--- include/infiniband/umad.h.orig	2015-03-03 20:04:43.000000000 +0000
+++ include/infiniband/umad.h	2015-07-22 04:52:34.000000000 +0000
@@ -36,7 +36,11 @@
 
 #include <stdint.h>
 #include <stdlib.h>
+#if defined(__linux__)
 #include <byteswap.h>
+#else
+#include <unistd.h>
+#endif
 #include <arpa/inet.h>
 
 #ifdef __cplusplus
@@ -87,11 +91,18 @@
 
 #define IB_IOCTL_MAGIC		0x1b
 
+#if defined(__linux__)
 #define IB_USER_MAD_REGISTER_AGENT	_IOWR(IB_IOCTL_MAGIC, 1, \
 					      struct ib_user_mad_reg_req)
 #define IB_USER_MAD_UNREGISTER_AGENT	_IOW(IB_IOCTL_MAGIC, 2, uint32_t)
 #define IB_USER_MAD_ENABLE_PKEY		_IO(IB_IOCTL_MAGIC, 3)
 #define IB_USER_MAD_REGISTER_AGENT2     _IOWR(IB_IOCTL_MAGIC, 4, \
 					      struct ib_user_mad_reg_req2)
+#else
+#define IB_USER_MAD_REGISTER_AGENT	_IO(IB_IOCTL_MAGIC, 1)
+#define IB_USER_MAD_UNREGISTER_AGENT	_IO(IB_IOCTL_MAGIC, 2)
+#define IB_USER_MAD_ENABLE_PKEY		_IO(IB_IOCTL_MAGIC, 3)
+#define IB_USER_MAD_REGISTER_AGENT2     _IO(IB_IOCTL_MAGIC, 4)
+#endif
 
 #define UMAD_CA_NAME_LEN	20
@@ -106,7 +117,11 @@
 
 #define UMAD_MAX_PORTS		64
 
+#if defined(__linux__)
 #define UMAD_DEV_DIR		"/dev/infiniband"
+#else
+#define UMAD_DEV_DIR		"/dev"
+#endif
 
 #define SYS_CA_PORTS_DIR	"ports"
 
