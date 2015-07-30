--- include/infiniband/mad_osd.h.orig	2015-07-30 04:45:57.000000000 +0000
+++ include/infiniband/mad_osd.h	2015-07-30 05:05:33.000000000 +0000
@@ -39,7 +39,12 @@
 #include <stdio.h>
 #include <sys/types.h>
 #include <unistd.h>
+#if defined(__linux__)
 #include <byteswap.h>
+#else
+#include <sys/endian.h>
+#include <sys/socket.h> /* For AF_INET6 */
+#endif
 #include <inttypes.h>
 #include <arpa/inet.h>
 
