--- ./include/opensm/osm_opensm.h.orig	2015-07-30 06:17:09.000000000 +0000
+++ ./include/opensm/osm_opensm.h	2015-07-30 05:56:58.000000000 +0000
@@ -44,6 +44,11 @@
 #ifndef _OSM_OPENSM_H_
 #define _OSM_OPENSM_H_
 
+#if ! defined(__linux__)
+#include <netinet/in.h>
+#include <sys/socket.h>
+#endif
+
 #include <stdio.h>
 #include <complib/cl_qlist.h>
 #include <complib/cl_dispatcher.h>
