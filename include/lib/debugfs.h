/*
 * Copyright (c) 2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DEBUGFS_H
#define DEBUGFS_H

#define NAMELEN   13 /* Maximum length of a file name */
#define PATHLEN   41 /* Maximum length of a path */
#define STATLEN   41 /* Size of static part of dir format */
#define ROOTLEN   (2 + 4) /* Size needed to encode root string */
#define FILNAMLEN (2 + NAMELEN) /* Size needed to encode filename */
#define DIRLEN    (STATLEN + FILNAMLEN + 3*ROOTLEN) /* Size of dir entry */

#define KSEEK_SET 0
#define KSEEK_CUR 1
#define KSEEK_END 2

#define NELEM(tab) (sizeof(tab) / sizeof((tab)[0]))

typedef unsigned short qid_t; /* FIXME: short type not recommended? */

/*******************************************************************************
 * This structure contains the necessary information to represent a 9p
 * directory.
 ******************************************************************************/
typedef struct {
	char		name[NAMELEN];
	long		length;
	unsigned char	mode;
	unsigned char	index;
	unsigned char	dev;
	qid_t		qid;
} dir_t;

/* Permission definitions used as flags */
#define O_READ		(1 << 0)
#define O_WRITE		(1 << 1)
#define O_RDWR		(1 << 2)
#define O_BIND		(1 << 3)
#define O_DIR		(1 << 4)
#define O_STAT		(1 << 5)

/* 9p interface */
int mount(const char *srv, const char *mnt, const char *spec);
int create(const char *name, int flags);
int open(const char *name, int flags);
int close(int fd);
int read(int fd, void *buf, int n);
int write(int fd, void *buf, int n);
int seek(int fd, long off, int whence);
int bind(const char *path, const char *where);
int stat(const char *path, dir_t *dir);

/* DebugFS initialization */
void debugfs_init(void);

#endif /* DEBUGFS_H */
