# $FreeBSD$

PORTNAME=	libibmad
PORTVERSION=	1.3.12
CATEGORIES=	sysutils
MASTER_SITES=	https://www.openfabrics.org/downloads/management/

MAINTAINER=	"Anthony Cornehl" <accornehl@fastmail.fm>

LIB_DEPENDS=	libibumad.so:${PORTSDIR}/sysutils/libibumad

GNU_CONFIGURE=
CFLAGS+=	-L${LOCALBASE}/lib -I${LOCALBASE}/include

.include <bsd.port.mk>
