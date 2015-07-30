--- include/infiniband/mad.h.orig	2015-07-30 04:52:02.000000000 +0000
+++ include/infiniband/mad.h	2015-07-30 05:00:05.000000000 +0000
@@ -36,6 +36,9 @@
 #define _MAD_H_
 
 #include <infiniband/mad_osd.h>
+#if ! defined(__GNU__)
+#include <errno.h>
+#endif
 
 #ifdef __cplusplus
 #  define BEGIN_C_DECLS extern "C" {
@@ -1660,6 +1663,10 @@
 
 extern MAD_EXPORT int ibdebug;
 
+#if ! defined(bswap_64)
+#define bswap_64 bswap64
+#endif
+
 #if __BYTE_ORDER == __LITTLE_ENDIAN
 #ifndef ntohll
 static inline uint64_t ntohll(uint64_t x)
@@ -1702,11 +1709,20 @@
 #define IBVERBOSE(fmt, ...) fprintf(stdout, "[%d] %s: " fmt "\n", \
 (int)getpid(), __func__, ## __VA_ARGS__)
 
+#if defined(__GNU__)
 #define IBPANIC(fmt, ...) do { \
 	fprintf(stderr, "ibpanic: [%d] %s: " fmt ": %m\n", \
 	(int)getpid(), __func__, ## __VA_ARGS__); \
 	exit(-1); \
 } while(0)
+#else
+#define IBPANIC(fmt, ...) do { \
+	fprintf(stderr, "ibpanic: [%d] %s: " fmt, \
+	(int)getpid(), __func__, ## __VA_ARGS__); \
+	fprintf(stderr, ": %s\n", strerror(errno)); \
+	exit(-1); \
+} while(0)
+#endif
 
 MAD_EXPORT void xdump(FILE * file, char *msg, void *p, int size);
 
