/*	$NetBSD: hash.h,v 1.26 2020/10/05 20:21:30 rillig Exp $	*/

/*
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)hash.h	8.1 (Berkeley) 6/6/93
 */

/*
 * Copyright (c) 1988, 1989 by Adam de Boor
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
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
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)hash.h	8.1 (Berkeley) 6/6/93
 */

/* Hash tables with strings as keys and arbitrary pointers as values. */

#ifndef	MAKE_HASH_H
#define	MAKE_HASH_H

/* A single key-value entry in the hash table. */
typedef struct Hash_Entry {
    struct Hash_Entry *next;	/* Used to link together all the entries
				 * associated with the same bucket. */
    void	      *value;
    unsigned	      namehash;	/* hash value of key */
    char	      name[1];	/* key string, variable length */
} Hash_Entry;

/* The hash table containing the entries. */
typedef struct Hash_Table {
    Hash_Entry **buckets;	/* Pointers to Hash_Entry, one
				 * for each bucket in the table. */
    unsigned int bucketsSize;
    unsigned int numEntries;	/* Number of entries in the table. */
    unsigned int bucketsMask;	/* Used to select the bucket for a hash. */
    unsigned int maxchain;	/* max length of chain detected */
} Hash_Table;

/*
 * The following structure is used by the searching routines
 * to record where we are in the search.
 */
typedef struct Hash_Search {
    Hash_Table *table;		/* Table being searched. */
    unsigned int nextBucket;	/* Next bucket to check (after current). */
    Hash_Entry *entry;		/* Next entry to check in current bucket. */
} Hash_Search;

static inline MAKE_ATTR_UNUSED void *
Hash_GetValue(Hash_Entry *h)
{
    return h->value;
}

static inline MAKE_ATTR_UNUSED void
Hash_SetValue(Hash_Entry *h, void *datum)
{
    h->value = datum;
}

void Hash_InitTable(Hash_Table *);
void Hash_DeleteTable(Hash_Table *);
Hash_Entry *Hash_FindEntry(Hash_Table *, const char *);
void *Hash_FindValue(Hash_Table *, const char *);
Hash_Entry *Hash_CreateEntry(Hash_Table *, const char *, Boolean *);
void Hash_DeleteEntry(Hash_Table *, Hash_Entry *);
Hash_Entry *Hash_EnumFirst(Hash_Table *, Hash_Search *);
Hash_Entry *Hash_EnumNext(Hash_Search *);
void Hash_ForEach(Hash_Table *, void (*)(void *, void *), void *);
void Hash_DebugStats(Hash_Table *, const char *);

#endif /* MAKE_HASH_H */
