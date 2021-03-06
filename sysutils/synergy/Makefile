# $FreeBSD$

PORTNAME=	synergy
PORTVERSION=	1.7.3
CATEGORIES=	sysutils

MAINTAINER=	kevlo@FreeBSD.org
COMMENT=	Mouse and keyboard sharing utility

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		cmake cpe
CPE_VENDOR=	synergy-foss
USE_XORG=	ice xtst x11 sm
USE_GITHUB=	yes

DISTVERSIONPREFIX=	v
DISTVERSIONSUFFIX=	-stable

LIB_DEPENDS=	libcurl.so:${PORTSDIR}/ftp/curl

MAKE_JOBS_UNSAFE=yes

CFLAGS+=	-I${LOCALBASE}/include -L${LOCALBASE}/lib

PLIST_FILES=    bin/synergyc bin/synergyd bin/synergys \
		man/man1/synergyc.1.gz man/man1/synergys.1.gz
PORTEXAMPLES=	synergy.conf.example synergy.conf.example-basic \
		synergy.conf.example-advanced

OPTIONS_DEFINE=	EXAMPLES

post-extract:
	cp ${WRKSRC}/LICENSE ${WRKSRC}/COPYING
	${MKDIR} -p ${WRKSRC}/ext/gmock-1.6.0 ${WRKSRC}/ext/gtest-1.6.0
	(cd ${WRKSRC}/ext/gmock-1.6.0 && ${TAR} xfz ../gmock-1.6.0.zip)
	(cd ${WRKSRC}/ext/gtest-1.6.0 && ${TAR} xfz ../gtest-1.6.0.zip)

do-install:
.for f in synergyc synergyd synergys
	${INSTALL_PROGRAM} ${WRKSRC}/bin/${f} ${STAGEDIR}${PREFIX}/bin
.endfor
	${INSTALL_MAN} ${WRKSRC}/doc/synergyc.man \
		${STAGEDIR}${MANPREFIX}/man/man1/synergyc.1
	${INSTALL_MAN} ${WRKSRC}/doc/synergys.man \
		${STAGEDIR}${MANPREFIX}/man/man1/synergys.1
	${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
.for f in ${PORTEXAMPLES}
	${INSTALL_DATA} ${WRKSRC}/doc/${f} ${STAGEDIR}${EXAMPLESDIR}
.endfor

.include <bsd.port.mk>
