# $FreeBSD$

PORTNAME=	opensm
PORTVERSION=	3.3.19
CATEGORIES=	sysutils
MASTER_SITES=	https://www.openfabrics.org/downloads/management/

MAINTAINER=	"Anthony Cornehl" <accornehl@fastmail.fm>

LIB_DEPENDS=	libibumad.so:${PORTSDIR}/sysutils/libibumad

USE_AUTOTOOLS=	aclocal autoheader automake autoconf
GNU_CONFIGURE=
CFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

.include <bsd.port.mk>
