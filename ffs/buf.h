/*	$NetBSD: buf.h,v 1.3 2013/01/26 00:19:39 christos Exp $	*/

/*
 * Copyright (c) 2001 Wasabi Systems, Inc.
 * All rights reserved.
 *
 * Written by Luke Mewburn for Wasabi Systems, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed for the NetBSD Project by
 *      Wasabi Systems, Inc.
 * 4. The name of Wasabi Systems, Inc. may not be used to endorse
 *    or promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY WASABI SYSTEMS, INC. ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL WASABI SYSTEMS, INC
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _FFS_BUF_H
#define	_FFS_BUF_H

#include <sys/param.h>
#include <sys/queue.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <err.h>

struct componentname {
	char *cn_nameptr;
	size_t cn_namelen;
};

struct vnode {
	int fd;
	void *fs;
	void *v_data;
	int offset;
};

#define vput(a) ((void)(a))

struct buf {
	void *		b_data;
	long		b_bufsize;
	long		b_bcount;
	daddr_t		b_blkno;
	daddr_t		b_lblkno;
	int		b_fd;
	struct fs *	b_fs;

	TAILQ_ENTRY(buf)	b_tailq;
};

void		bcleanup(void);
int		bread(struct vnode *, daddr_t, int, struct kauth_cred *,
    int, struct buf **);
void		brelse(struct buf *, int);
int		bwrite(struct buf *);
struct buf *	getblk(struct vnode *, daddr_t, int, int, int);

#define	bdwrite(bp)	bwrite(bp)
#define	clrbuf(bp)	memset((bp)->b_data, 0, (u_int)(bp)->b_bcount)

#define	B_MODIFY	0
#define	BC_AGE		0

#define min(a, b) MIN((a), (b))
#define microtime(tv) gettimeofday((tv), NULL)
#define KASSERT(a)
#define IO_SYNC	1

struct pool {
	size_t size;
};

#define pool_init(p, s, a1, a2, a3, a4, a5, a6)	(p)->size = (s)
#define pool_get(p, f)	malloc((p)->size)
#define pool_put(p, a)	free(a)
#define pool_destroy(p)

#define MALLOC_DECLARE(a)
#define malloc_type_attach(a)
#define malloc_type_detach(a)

#define mutex_enter(m)
#define mutex_exit(m)
#define mutex_init(m, t, i)
#define mutex_destroy(m)

#define desiredvnodes 10000

#endif	/* _FFS_BUF_H */
