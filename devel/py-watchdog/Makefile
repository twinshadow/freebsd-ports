# $FreeBSD$

PORTNAME=	watchdog
PORTVERSION=	0.8.2
DISTVERSIONPREFIX=	v
PORTREVISION=	0
CATEGORIES=	devel
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	nivit@FreeBSD.org
COMMENT=	Python API library to monitor file system events

LICENSE=	APACHE20

RUN_DEPENDS=	${PKGNAMEPREFIX}argh>=0.24.1:${PORTSDIR}/devel/py-argh \
		${PKGNAMEPREFIX}pathtools>=0.1.2:${PORTSDIR}/devel/py-pathtools \
		${PKGNAMEPREFIX}yaml>=3.10:${PORTSDIR}/devel/py-yaml

DOCS_BUILD_DEPENDS=	${PKGNAMEPREFIX}pathtools>=0.1.2:${PORTSDIR}/devel/py-pathtools \
		${PKGNAMEPREFIX}sphinx>=1.1.3:${PORTSDIR}/textproc/py-sphinx
DOCSDIR=	${PREFIX}/share/doc/${PKGNAMEPREFIX}${PORTNAME}

GH_ACCOUNT=	gorakhargosh

OPTIONSFILE=	${PORT_DBDIR}/py-${PORTNAME}/options
OPTIONS_DEFINE=	DOCS

PORTDOCS=	*

USE_GITHUB=	yes
USES=		python
USE_PYTHON=	autoplist distutils

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MDOCS}
post-build:
	(cd ${WRKSRC}/docs ; ${MAKE} html)

post-install:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	(cd ${WRKSRC}/docs/build/html ; \
	${COPYTREE_SHARE} . ${STAGEDIR}${DOCSDIR} "-not -name .buildinfo")
.endif

.include <bsd.port.mk>
