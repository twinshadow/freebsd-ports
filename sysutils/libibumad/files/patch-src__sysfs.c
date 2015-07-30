--- src/sysfs.c.orig	2013-03-06 16:25:35.000000000 +0000
+++ src/sysfs.c	2015-07-22 05:22:11.000000000 +0000
@@ -46,13 +46,22 @@
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
+#if defined(__linux__)
 #include <endian.h>
-#include <byteswap.h>
+#else
+#include <dirent.h>
+#include <sys/endian.h>
+#include <sys/sysctl.h>
+#endif
 #include <netinet/in.h>
 
 #if __BYTE_ORDER == __LITTLE_ENDIAN
+#if defined(__linux__)
 #define htonll(x) bswap_64(x)
 #else
+#define htonll(x) bswap64(x)
+#endif
+#else
 #define htonll(x) (x)
 #endif
 
@@ -68,10 +77,15 @@
 int sys_read_string(const char *dir_name, const char *file_name, char *str, int max_len)
 {
 	char path[256], *s;
+#if defined(__linux__)
 	int fd, r;
+#else
+	size_t len;
+#endif
 
 	snprintf(path, sizeof(path), "%s/%s", dir_name, file_name);
 
+#if defined(__linux__)
 	if ((fd = open(path, O_RDONLY)) < 0)
 		return ret_code();
 
@@ -83,11 +97,24 @@
 	}
 
 	str[(r < max_len) ? r : max_len - 1] = 0;
+#else
+	for (s = &path[0]; *s != '\0'; s++)
+		if (*s == '/')
+			*s = '.';
+
+	len = max_len;
+	if (sysctlbyname(&path[1], str, &len, NULL, 0) == -1)
+		return ret_code();
+
+	str[(len < max_len) ? len : max_len - 1] = 0;
+#endif
 
 	if ((s = strrchr(str, '\n')))
 		*s = 0;
 
+#if defined(__linux__)
 	close(fd);
+#endif
 	return 0;
 }
 
@@ -156,3 +183,130 @@
 
 	return 0;
 }
+
+#define	DIRECTSIZ(namlen)						\
+	(((uintptr_t)&((struct dirent *)0)->d_name +			\
+	((namlen)+1)*sizeof(((struct dirent *)0)->d_name[0]) + 3) & ~3)
+
+int
+sys_scandir(const char *dirname, struct dirent ***namelist,
+    int (*select)(const struct dirent *),
+    int (*compar)(const struct dirent **, const struct dirent **))
+{
+	struct dirent **names;
+	struct dirent **names2;
+	struct dirent *dp;
+	char name[1024];
+	int lsname[22];
+	int chname[22];
+	int name2[22];
+	int oid[22];
+	char *s;
+	size_t n1, n2;
+	size_t len, oidlen, namlen;
+	int cnt, max;
+	int err;
+	int i;
+
+	*namelist = NULL;
+	/* Skip the leading / */
+	strncpy(name, &dirname[1], sizeof(name));
+	for (s = &name[0]; *s != '\0'; s++)
+		if (*s == '/')
+			*s = '.';
+	/*
+	 * Resolve the path.
+	 */
+	len = sizeof(oid) / sizeof(int);
+	namlen = strlen(name) + 1;
+	if (sysctlnametomib(name, oid, &len) != 0)
+		return (-errno);
+	lsname[0] = 0;	/* Root */
+	lsname[1] = 2;	/* Get next */
+	memcpy(lsname+2, oid, len * sizeof(int));
+	n1 = 2 + len;
+	oidlen = len;
+	/*
+	 * Setup the return list of dirents.
+	 */
+	cnt = 0;
+	max = 64;
+	names = malloc(max * sizeof(void *));
+	if (names == NULL)
+		return (-ENOMEM);
+
+	for (;;) {
+		n2 = sizeof(name2);
+		if (sysctl(lsname, n1, name2, &n2, 0, 0) < 0) {
+			if (errno == ENOENT)
+				break;
+			goto errout;
+		}
+		n2 /= sizeof(int);
+		if (n2 < oidlen)
+			break;
+		for (i = 0; i < oidlen; i++)
+			if (name2[i] != oid[i])
+				goto out;
+		chname[0] = 0;	/* root */
+		chname[1] = 1;	/* oid name */
+		memcpy(chname + 2, name2, n2 * sizeof(int));
+		memcpy(lsname + 2, name2, n2 * sizeof(int));
+		n1 = 2 + n2;
+		/*
+		 * scandir() is not supposed to go deeper than the requested
+		 * directory but sysctl also doesn't return a node for
+		 * 'subdirectories' so we have to find a file in the subdir
+		 * and then truncate the name to report it.
+		 */
+		if (n2 > oidlen + 1) {
+			/* Skip to the next name after this one. */
+			n1 = 2 + oidlen + 1;
+			lsname[n1 - 1]++;
+		}
+		len = sizeof(name);
+		if (sysctl(chname, n2 + 2, name, &len, 0, 0) < 0)
+			goto errout;
+		if (len <= 0 || len < namlen)
+			goto out;
+		s = name + namlen;
+		/* Just keep the first level name. */
+		if (strchr(s, '.'))
+			*strchr(s, '.') = '\0';
+		len = strlen(s) + 1;
+		dp = malloc(DIRECTSIZ(len));
+		dp->d_reclen = DIRECTSIZ(len);
+		dp->d_namlen = len;
+		memcpy(&dp->d_name, s, len);
+		if (select && !select(dp)) {
+			free(dp);
+			continue;
+		}
+		if (cnt == max) {
+			max *= 2;
+			names2 = realloc(names, max * sizeof(void *));
+			if (names2 == NULL) {
+				errno = ENOMEM;
+				free(dp);
+				goto errout;
+			}
+			names = names2;
+		}
+		names[cnt++] = dp;
+	}
+out:
+	if (cnt && compar)
+		qsort(names, cnt, sizeof(struct dirent *),
+		    (int (*)(const void *, const void *))compar);
+
+	*namelist = names;
+
+	return (cnt);
+
+errout:
+	err = errno;
+	for (i = 0; i < cnt; i++)
+		free(names[i]);
+	free(names);
+	return (-err);
+}
