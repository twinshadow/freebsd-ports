--- ./include/complib/cl_debug_osd.h.orig	2015-07-30 06:17:01.000000000 +0000
+++ ./include/complib/cl_debug_osd.h	2015-07-30 05:55:23.000000000 +0000
@@ -42,7 +42,11 @@
 #define _CL_DEBUG_OSD_H_
 
 #include <complib/cl_types.h>
+#if defined(__linux__)
 #include <bits/wordsize.h>
+#else
+#include <stdint.h>
+#endif
 
 #ifdef __cplusplus
 #  define BEGIN_C_DECLS extern "C" {
