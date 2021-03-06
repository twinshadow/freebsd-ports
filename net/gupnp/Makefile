# Created by: Martin Wilke <miwi@FreeBSD.org>
# $FreeBSD$

PORTNAME=	gupnp
PORTVERSION=	0.20.14
CATEGORIES=	net
MASTER_SITES=	GNOME

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Framework for UPnP devices

LICENSE=	LGPL20

BUILD_DEPENDS=	gobject-introspection>=0.6.4:${PORTSDIR}/devel/gobject-introspection
LIB_DEPENDS=	libgssdp-1.0.so:${PORTSDIR}/net/gssdp \
		libsoup-2.4.so:${PORTSDIR}/devel/libsoup \
		libuuid.so:${PORTSDIR}/misc/e2fsprogs-libuuid

CONFIGURE_ARGS=	--enable-introspection=yes
CONFIGURE_ENV=	VAPIGEN="" ac_cv_path_VAPIGEN=""
GNU_CONFIGURE=	yes
INSTALL_TARGET=	install-strip
USE_GNOME=	glib20 introspection:build
USE_LDCONFIG=	yes
USE_CSTD=	c11
USES=		compiler:c11 gmake libtool pathfix pkgconfig python:run shebangfix tar:xz

SHEBANG_FILES=	tools/gupnp-binding-tool
python_CMD=	${PYTHON_CMD}

.include <bsd.port.pre.mk>

.if ${CHOSEN_COMPILER_TYPE} == "clang"
CPPFLAGS+=	-Wno-return-type
.endif

.include <bsd.port.post.mk>
