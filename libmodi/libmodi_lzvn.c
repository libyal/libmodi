/*
 * LZVN (un)compression functions
 *
 * Copyright (C) 2012-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libmodi_libcerror.h"
#include "libmodi_libcnotify.h"
#include "libmodi_lzvn.h"

enum LIBMODI_LZVN_OPPCODE_TYPES
{
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,
	LIBMODI_LZVN_OPPCODE_TYPE_END_OF_STREAM,
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_LARGE,
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_LARGE,
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,
	LIBMODI_LZVN_OPPCODE_TYPE_NONE,
};

/* Lookup table to map an oppcode to its type
 */
uint8_t libmodi_lzvn_oppcode_types[ 256 ] = {
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x00 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x01 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x02 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x03 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x04 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x05 */
	LIBMODI_LZVN_OPPCODE_TYPE_END_OF_STREAM,	/* 0x06 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x07 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x08 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x09 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x0a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x0b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x0c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x0d */
	LIBMODI_LZVN_OPPCODE_TYPE_NONE,			/* 0x0e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x0f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x10 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x11 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x12 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x13 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x14 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x15 */
	LIBMODI_LZVN_OPPCODE_TYPE_NONE,			/* 0x16 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x17 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x18 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x19 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x1a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x1b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x1c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x1d */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x1e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x1f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x20 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x21 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x22 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x23 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x24 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x25 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x26 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x27 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x28 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x29 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x2a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x2b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x2c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x2d */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x2e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x2f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x30 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x31 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x32 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x33 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x34 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x35 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x36 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x37 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x38 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x39 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x3a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x3b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x3c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x3d */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x3e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x3f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x40 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x41 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x42 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x43 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x44 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x45 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x46 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x47 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x48 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x49 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x4a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x4b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x4c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x4d */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x4e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x4f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x50 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x51 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x52 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x53 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x54 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x55 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x56 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x57 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x58 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x59 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x5a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x5b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x5c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x5d */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x5e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x5f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x60 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x61 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x62 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x63 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x64 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x65 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x66 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x67 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x68 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x69 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x6a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x6b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x6c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x6d */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x6e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x6f */

	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x70 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x71 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x72 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x73 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x74 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x75 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x76 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x77 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x78 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x79 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x7a */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x7b */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x7c */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x7d */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x7e */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0x7f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x80 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x81 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x82 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x83 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x84 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x85 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x86 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x87 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x88 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x89 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x8a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x8b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x8c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x8d */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x8e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x8f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x90 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x91 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x92 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x93 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x94 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x95 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x96 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x97 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x98 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x99 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x9a */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x9b */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x9c */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0x9d */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0x9e */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0x9f */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa0 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa1 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa2 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa3 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa4 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa5 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa6 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa7 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa8 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xa9 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xaa */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xab */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xac */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xad */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xae */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xaf */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb0 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb1 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb2 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb3 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb4 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb5 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb6 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb7 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb8 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xb9 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xba */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xbb */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xbc */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xbd */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xbe */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM,	/* 0xbf */

	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xc0 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xc1 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xc2 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xc3 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xc4 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xc5 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0xc6 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0xc7 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xc8 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xc9 */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xca */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xcb */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xcc */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL,	/* 0xcd */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS,	/* 0xce */
	LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE,	/* 0xcf */

	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd0 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd1 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd2 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd3 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd4 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd5 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd6 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd7 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd8 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xd9 */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xda */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xdb */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xdc */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xdd */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xde */
	LIBMODI_LZVN_OPPCODE_TYPE_INVALID,		/* 0xdf */

	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_LARGE,	/* 0xe0 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe1 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe2 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe3 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe4 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe5 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe6 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe7 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe8 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xe9 */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xea */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xeb */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xec */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xed */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xee */
	LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL,	/* 0xef */

	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_LARGE,		/* 0xf0 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf1 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf2 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf3 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf4 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf5 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf6 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf7 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf8 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xf9 */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xfa */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xfb */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xfc */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xfd */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xfe */
	LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL,		/* 0xff */
};

/* Decompresses LZVN compressed data
 * Returns 1 on success or -1 on error
 */
int libmodi_lzvn_decompress(
     const uint8_t *compressed_data,
     size_t compressed_data_size,
     uint8_t *uncompressed_data,
     size_t *uncompressed_data_size,
     libcerror_error_t **error )
{
	static char *function              = "libmodi_lzvn_decompress";
	size_t compressed_data_offset      = 0;
	size_t match_offset                = 0;
	size_t safe_uncompressed_data_size = 0;
	size_t uncompressed_data_offset    = 0;
	uint16_t distance                  = 0;
	uint16_t literal_size              = 0;
	uint16_t match_size                = 0;
	uint8_t oppcode                    = 0;
	uint8_t oppcode_type               = 0;
	uint8_t oppcode_value              = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	size_t debug_match_offset          = 0;
	size_t oppcode_data_offset         = 0;
	size_t oppcode_data_size           = 0;
	uint16_t debug_match_size          = 0;
#endif

	if( compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed data.",
		 function );

		return( -1 );
	}
	if( compressed_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid compressed data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( uncompressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid uncompressed data.",
		 function );

		return( -1 );
	}
	if( uncompressed_data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid uncompressed data size.",
		 function );

		return( -1 );
	}
	safe_uncompressed_data_size = *uncompressed_data_size;

	if( safe_uncompressed_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid uncompressed data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	while( compressed_data_offset < compressed_data_size )
	{
		if( uncompressed_data_offset >= safe_uncompressed_data_size )
		{
			break;
		}
		if( compressed_data_offset >= compressed_data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: compressed data size value too small.",
			 function );

			return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		oppcode_data_offset = compressed_data_offset;
		oppcode_data_size   = 1;
#endif
		oppcode = compressed_data[ compressed_data_offset++ ];

		oppcode_type = libmodi_lzvn_oppcode_types[ oppcode ];

		literal_size = 0;
		match_size   = 0;

		switch( oppcode_type )
		{
			case LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_LARGE:
#if defined( HAVE_DEBUG_OUTPUT )
				oppcode_data_size += 2;
#endif
				if( ( compressed_data_offset + 1 ) >= compressed_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: compressed data size value too small.",
					 function );

					return( -1 );
				}
				oppcode_value = compressed_data[ compressed_data_offset++ ];

				literal_size = ( oppcode & 0xc0 ) >> 6;
				match_size   = ( ( oppcode & 0x38 ) >> 3 ) + 3;
				distance     = ( (uint16_t) compressed_data[ compressed_data_offset++ ] << 8 ) | oppcode_value;

				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_MEDIUM:
#if defined( HAVE_DEBUG_OUTPUT )
				oppcode_data_size += 2;
#endif
				if( ( compressed_data_offset + 1 ) >= compressed_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: compressed data size value too small.",
					 function );

					return( -1 );
				}
				oppcode_value = compressed_data[ compressed_data_offset++ ];

				literal_size = ( oppcode & 0x18 ) >> 3;
				match_size   = ( ( ( oppcode & 0x07 ) << 2 ) | ( oppcode_value & 0x03 ) ) + 3;
				distance     = ( (uint16_t) compressed_data[ compressed_data_offset++ ] << 6 ) | ( ( oppcode_value & 0xfc ) >> 2 );

				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_PREVIOUS:
				literal_size = ( oppcode & 0xc0 ) >> 6;
				match_size   = ( ( oppcode & 0x38 ) >> 3 ) + 3;

				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_DISTANCE_SMALL:
#if defined( HAVE_DEBUG_OUTPUT )
				oppcode_data_size += 1;
#endif
				if( compressed_data_offset >= compressed_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: compressed data size value too small.",
					 function );

					return( -1 );
				}
				literal_size = ( oppcode & 0xc0 ) >> 6;
				match_size   = ( ( oppcode & 0x38 ) >> 3 ) + 3;
				distance     = ( (uint16_t) ( oppcode & 0x07 ) << 8 ) | compressed_data[ compressed_data_offset++ ];

				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_LARGE:
#if defined( HAVE_DEBUG_OUTPUT )
				oppcode_data_size += 1;
#endif
				if( compressed_data_offset >= compressed_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: compressed data size value too small.",
					 function );

					return( -1 );
				}
				literal_size = (uint16_t) compressed_data[ compressed_data_offset++ ] + 16;

				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_LITERAL_SMALL:
				literal_size = oppcode & 0x0f;

				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_MATCH_LARGE:
#if defined( HAVE_DEBUG_OUTPUT )
				oppcode_data_size += 1;
#endif
				if( compressed_data_offset >= compressed_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: compressed data size value too small.",
					 function );

					return( -1 );
				}
				match_size = (uint16_t) compressed_data[ compressed_data_offset++ ] + 16;

				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_MATCH_SMALL:
				match_size = oppcode & 0x0f;

				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_END_OF_STREAM:
			case LIBMODI_LZVN_OPPCODE_TYPE_NONE:
				break;

			case LIBMODI_LZVN_OPPCODE_TYPE_INVALID:
			default:
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: invalid oppcode: 0x%02" PRIx8 ".",
				 function,
				 oppcode );

				return( -1 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: oppcode data:\n",
			 function );
			libcnotify_print_data(
			 &( compressed_data[ oppcode_data_offset ] ),
			 oppcode_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

			libcnotify_printf(
			 "%s: oppcode\t\t\t\t\t\t: 0x%02" PRIx8 "\n",
			 function,
			 oppcode );

			libcnotify_printf(
			 "%s: literal size\t\t\t\t\t\t: %" PRIu16 "\n",
			 function,
			 literal_size );

			libcnotify_printf(
			 "%s: match size\t\t\t\t\t\t: %" PRIu16 "\n",
			 function,
			 match_size );

			libcnotify_printf(
			 "%s: distance\t\t\t\t\t\t: %" PRIu16 "\n",
			 function,
			 distance );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( oppcode_type == LIBMODI_LZVN_OPPCODE_TYPE_END_OF_STREAM )
		{
			break;
		}
		if( literal_size > 0 )
		{
			if( ( (size_t) literal_size > compressed_data_size )
			 || ( compressed_data_offset > ( compressed_data_size - literal_size ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: literal size value exceeds compressed data size.",
				 function );

				return( -1 );
			}
			if( ( (size_t) literal_size > safe_uncompressed_data_size )
			 || ( uncompressed_data_offset > ( safe_uncompressed_data_size - literal_size ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: literal size value exceeds uncompressed data size.",
				 function );

				return( -1 );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: literal:\n",
				 function );
				libcnotify_print_data(
				 &( compressed_data[ compressed_data_offset ] ),
				 literal_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			if( memory_copy(
			     &( uncompressed_data[ uncompressed_data_offset ] ),
			     &( compressed_data[ compressed_data_offset ] ),
			     (size_t) literal_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy literal to uncompressed data.",
				 function );

				return( -1 );
			}
			compressed_data_offset   += (size_t) literal_size;
			uncompressed_data_offset += (size_t) literal_size;
		}
		if( match_size > 0 )
		{
			if( (size_t) distance > uncompressed_data_offset )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: distance value exceeds uncompressed data offset.",
				 function );

				return( -1 );
			}
			match_offset = uncompressed_data_offset - distance;

			if( ( (size_t) match_size > safe_uncompressed_data_size )
			 || ( uncompressed_data_offset > ( safe_uncompressed_data_size - match_size ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: match size value exceeds uncompressed data size.",
				 function );

				return( -1 );
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				debug_match_offset = match_offset;
				debug_match_size   = match_size;

				libcnotify_printf(
				 "%s: match offset\t\t\t\t\t\t: 0x%" PRIzx "\n",
				 function,
				 debug_match_offset );
			}
#endif
			while( match_size > 0 )
			{
				uncompressed_data[ uncompressed_data_offset++ ] = uncompressed_data[ match_offset++ ];

				match_size--;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: match:\n",
				 function );
				libcnotify_print_data(
				 &( uncompressed_data[ debug_match_offset ] ),
				 debug_match_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
		}
	}
	*uncompressed_data_size = uncompressed_data_offset;

	return( 1 );
}

