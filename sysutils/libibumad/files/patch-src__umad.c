--- src/umad.c.orig	2015-07-22 05:06:31.000000000 +0000
+++ src/umad.c	2015-07-22 05:12:23.000000000 +0000
@@ -187,7 +187,11 @@
 	memcpy(&port->port_guid, gid + 8, sizeof port->port_guid);
 
 	snprintf(port_dir + len, sizeof(port_dir) - len, "/pkeys");
+#if defined(__linux__)
 	num_pkeys = scandir(port_dir, &namelist, check_for_digit_name, NULL);
+#else
+	num_pkeys = sys_scandir(port_dir, &namelist, check_for_digit_name, NULL);
+#endif
 	if (num_pkeys <= 0) {
 		IBWARN("no pkeys found for %s:%u (at dir %s)...",
 		       port->ca_name, port->portnum, port_dir);
@@ -387,7 +391,9 @@
 
 static int get_ca(const char *ca_name, umad_ca_t * ca)
 {
+#if defined(__linux__)
 	DIR *dir;
+#endif
 	char dir_name[256];
 	struct dirent **namelist;
 	int r, i, ret;
@@ -420,10 +426,14 @@
 	snprintf(dir_name, sizeof(dir_name), "%s/%s/%s",
 		 SYS_INFINIBAND, ca->ca_name, SYS_CA_PORTS_DIR);
 
+#if defined(__linux__)
 	if (!(dir = opendir(dir_name)))
 		return -ENOENT;
 
 	if ((r = scandir(dir_name, &namelist, 0, alphasort)) < 0) {
+#else
+	if ((r = sys_scandir(dir_name, &namelist, 0, alphasort)) < 0) {
+#endif
 		ret = errno < 0 ? errno : -EIO;
 		goto error;
 	}
@@ -460,7 +470,9 @@
 		free(namelist[i]);
 	free(namelist);
 
+#if defined(__linux__)
 	closedir(dir);
+#endif
 	put_ca(ca);
 	return 0;
 
@@ -469,7 +481,9 @@
 		free(namelist[i]);
 	free(namelist);
 error:
+#if defined(__linux__)
 	closedir(dir);
+#endif
 	release_ca(ca);
 
 	return ret;
@@ -563,7 +577,11 @@
 
 	TRACE("max %d", max);
 
+#if defined(__linux__)
 	n = scandir(SYS_INFINIBAND, &namelist, 0, alphasort);
+#else
+	n = sys_scandir(SYS_INFINIBAND, &namelist, 0, alphasort);
+#endif
 	if (n > 0) {
 		for (i = 0; i < n; i++) {
 			if (strcmp(namelist[i]->d_name, ".") &&
