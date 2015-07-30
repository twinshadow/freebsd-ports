--- ./osmtest/include/osmtest.h.orig	2015-07-30 06:17:15.000000000 +0000
+++ ./osmtest/include/osmtest.h	2015-07-30 06:01:57.000000000 +0000
@@ -43,6 +43,11 @@
 #ifndef _OSMTEST_H_
 #define _OSMTEST_H_
 
+#if ! defined(__linux__)
+#include <netinet/in.h>
+#include <sys/socket.h>
+#endif
+
 #include <complib/cl_qmap.h>
 #include <opensm/osm_log.h>
 #include <vendor/osm_vendor_api.h>
