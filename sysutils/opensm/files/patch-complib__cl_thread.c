--- ./complib/cl_thread.c.orig	2015-07-30 06:16:49.000000000 +0000
+++ ./complib/cl_thread.c	2015-07-30 05:50:32.000000000 +0000
@@ -39,7 +39,9 @@
 
 #include <stdio.h>
 #include <unistd.h>
+#if defined(__linux__)
 #include <sys/sysinfo.h>
+#endif
 #include <complib/cl_thread.h>
 
 /*
@@ -122,7 +124,11 @@
 {
 	uint32_t ret;
 
+#if defined(__linux__)
 	ret = get_nprocs();
+#else
+	ret = sysconf(_SC_NPROCESSORS_ONLN);
+#endif
 	if (!ret)
 		return 1;	/* Workaround for PPC where get_nprocs() returns 0 */
 
