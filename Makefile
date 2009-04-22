#	$NetBSD: Makefile,v 1.25 2009/04/22 15:23:05 lukem Exp $
#

WARNS?=	3	# XXX -Wsign-compare

.include <bsd.own.mk>

PROG=	makefs
SRCS=	cd9660.c ffs.c \
	getid.c \
	makefs.c misc.c \
	pack_dev.c \
	spec.c \
	walk.c
MAN=	makefs.8

MKNODSRC=	${NETBSDSRCDIR}/sbin/mknod
MTREESRC=	${NETBSDSRCDIR}/usr.sbin/mtree

CPPFLAGS+=	-I${.CURDIR} -I${MKNODSRC} -I${MTREESRC}
.PATH:		${MKNODSRC} ${MTREESRC}

.include "${.CURDIR}/cd9660/Makefile.inc"
.include "${.CURDIR}/ffs/Makefile.inc"

.if (${HOSTPROG:U} == "")
DPADD+= ${LIBUTIL}
LDADD+= -lutil
.endif

.include <bsd.prog.mk>
