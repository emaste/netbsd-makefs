#	$NetBSD: Makefile,v 1.28 2011/07/18 21:22:55 tron Exp $
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

.if !defined(HOSTPROG)
SRCS+=		v7fs.c
CPPFLAGS+=	-DUSE_V7FS

.include "${.CURDIR}/v7fs/Makefile.inc"

DPADD+= ${LIBUTIL}
LDADD+= -lutil
.endif

.include <bsd.prog.mk>
