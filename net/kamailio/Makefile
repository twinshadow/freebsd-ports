# Created by: Oliver Mahmoudi <olivermahmoudi@gmail.com>
# $FreeBSD$
#

PORTNAME=	kamailio
PORTVERSION=	4.2.4
CATEGORIES=	net
MASTER_SITES=	http://www.kamailio.org/pub/kamailio/${PORTVERSION}/src/
DISTNAME=	${PORTNAME}-${PORTVERSION}_src

MAINTAINER=	pi@FreeBSD.org
COMMENT=	Very fast and configurable open source SIP proxy

LICENSE=	GPLv2

LIB_DEPENDS=	libexpat.so:${PORTSDIR}/textproc/expat2 \
		libxml2.so:${PORTSDIR}/textproc/libxml2 \
		libcurl.so:${PORTSDIR}/ftp/curl
RUN_DEPENDS=	${LOCALBASE}/bin/bash:${PORTSDIR}/shells/bash

USES=		gmake shebangfix readline
USE_LDCONFIG=	yes
SHEBANG_FILES=	utils/kamctl/kamctl utils/kamctl/kamdbctl
CFLAGS+=	-Wall

WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION}

USE_RC_SUBR=	kamailio

USERS=		kamailio
GROUPS=		kamailio

OPTIONS_DEFINE=	DOCS MYSQL PGSQL RADIUS JITSI JABBER TLS UNIXODBC PRESENCE
OPTIONS_DEFAULT=MYSQL RADIUS JABBER TLS PRESENCE
OPTIONS_SUB=	YES

JITSI_DESC=	VoIP Frontend GUI via Jitsi
PRESENCE_DESC=	Presence support

MYSQL_USE=	mysql=yes
PGSQL_USES=	pgsql
JITSI_RUN_DEPENDS=	jitsi:${PORTSDIR}/net-im/jitsi
UNIXODBC_LIB_DEPENDS=	libodbc.so:${PORTSDIR}/databases/unixODBC
RADIUS_LIB_DEPENDS=	libradiusclient-ng.so:${PORTSDIR}/net/radiusclient
TLS_USE=		OPENSSL=yes

.include <bsd.port.options.mk>

.if ${OPSYS} == FreeBSD && ${OSVERSION} < 900000
BUILD_DEPENDS+=	clang33:${PORTSDIR}/lang/clang33
.endif

DEFAULT_GROUP_INCLUDE=	standard standard-dep

.if ${PORT_OPTIONS:MMYSQL}
EXTRA_GROUPS+=	mysql
.endif

.if ${PORT_OPTIONS:MPGSQL}
EXTRA_GROUPS+=	postgres
.endif

.if ${PORT_OPTIONS:MUNIXODBC}
EXTRA_MODULES+=	db_unixodbc
.endif

.if ${PORT_OPTIONS:MRADIUS}
EXTRA_GROUPS+=	radius
.endif

.if ${PORT_OPTIONS:MJABBER}
EXTRA_MODULES+=	jabber
.endif

.if ${PORT_OPTIONS:MTLS}
EXTRA_MODULES+=	tls
.endif

.if ${PORT_OPTIONS:MPRESENCE}
EXTRA_GROUPS+=	presence
.endif

.if !empty (EXTRA_GROUPS)
MAKE_ARGS+=	group_include="${DEFAULT_GROUP_INCLUDE} ${EXTRA_GROUPS}"
.else
MAKE_ARGS+=	group_include="${DEFAULT_GROUP_INCLUDE}"
.endif

.if !empty (EXTRA_MODULES)
MAKE_ARGS+=	include_modules="${EXTRA_MODULES}"
.endif

post-patch:
.if ! ${PORT_OPTIONS:MDOCS}
	${REINPLACE_CMD} -e 's#install-doc install-man#install-man#'	\
		${WRKSRC}/Makefile
.endif
.if ${OPSYS} == FreeBSD && ${OSVERSION} < 900000
	${REINPLACE_CMD} -e 's/clang/clang33/g' ${WRKSRC}/Makefile.defs
.endif

pre-build:
	cd ${WRKSRC} && ${GMAKE} ${MAKE_ARGS} cfg

do-build:
	cd ${WRKSRC} && ${GMAKE} ${ALL_TARGET}

post-stage:
# Do not install anything beyond ${PREFIX}
	${RM} /root/.rnd

# Strip modules in lib/kamailio/modules
	@${ECHO_CMD} "Stripping modules in ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/modules/"

.for i in db_mysql db_postgres db_unixodbc tls blst \
	xhttp_rpc nat_traversal print msrp mi_datagram \
	userblacklist msilo uid_uri_db drouting enum \
	p_usrloc avpops matrix rr sst \
	rtpproxy rtpproxy-ng mohqueue mqueue tmx sqlops dialog \
	usrloc dispatcher auth_db uac permissions \
	path tm mediaproxy nathelper print_lib \
	mangler group textops rtimer db_cluster \
	textopsx db_flatstore sl pipelimit counters \
	mi_fifo statistics stun cnxcc corex debugger pv \
	ratelimit ctl db2_ops mi_rpc tmrec \
	benchmark domainpolicy acc exec siputils \
	malloc_test kex cfg_rpc diversion ipops \
	uid_auth_db imc cfg_db xhttp seas \
	timer auth_diameter dmq uac_redirect pdt \
	call_control uri_db alias_db sca avp \
	cfgutils pike uid_domain domain maxfwd \
	htable topoh auth sms async \
	prefix_route speeddial registrar mtree uid_avp_db \
	xlog sipt siptrace qos pdb xprint auth_radius \
	sanity uid_gflags db_text sdpops sipcapture \
	tsilo nosip rtpengine jsonrpc-s \
	presence presence_conference presence_dialog presence_dialoginfo \
	presence_mwi \
	presence_profile presence_reginfo presence_xml pua_bla \
	pua_dialoginfo pua_mi pua_reginfo pua_usrloc rls \
	acc_radius misc_radius peering pua pua_xmpp xcap_client xcap_server
	@if [ -e ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/modules/${i}.so ]; then \
		${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/modules/${i}.so; \
	fi
.endfor

# Strip libraries in lib/kamailio
	@${ECHO_CMD} "Stripping libraries in ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/"

.for j in srdb2 srdb1 kcore srutils kmi trie print
	@if [ -e ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/lib${j}.so.1 ]; then \
		${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/lib${j}.so.1; \
	fi
.endfor

# This is also part of lib/kamailio but ends in .so.0
	@if [ -e ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/libbinrpc.so.0 ]; then \
		${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/${PORTNAME}/libbinrpc.so.0; \
	fi

# Strip binaries in sbin
	@${ECHO_CMD} "Stripping binaries in ${STAGEDIR}${PREFIX}/sbin/"

.for k in kamailio kamcmd
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/${k}
.endfor

do-install:
	cd ${WRKSRC} && ${GMAKE} ${INSTALL_TARGET}

.include <bsd.port.mk>
