/*
 * Codepage definitions for libmodi
 *
 * Copyright (C) 2012-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBMODI_CODEPAGE_H )
#define _LIBMODI_CODEPAGE_H

#include <libmodi/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBMODI_CODEPAGES
{
	LIBMODI_CODEPAGE_ASCII				= 20127,

	LIBMODI_CODEPAGE_ISO_8859_1			= 28591,
	LIBMODI_CODEPAGE_ISO_8859_2			= 28592,
	LIBMODI_CODEPAGE_ISO_8859_3			= 28593,
	LIBMODI_CODEPAGE_ISO_8859_4			= 28594,
	LIBMODI_CODEPAGE_ISO_8859_5			= 28595,
	LIBMODI_CODEPAGE_ISO_8859_6			= 28596,
	LIBMODI_CODEPAGE_ISO_8859_7			= 28597,
	LIBMODI_CODEPAGE_ISO_8859_8			= 28598,
	LIBMODI_CODEPAGE_ISO_8859_9			= 28599,
	LIBMODI_CODEPAGE_ISO_8859_10			= 28600,
	LIBMODI_CODEPAGE_ISO_8859_11			= 28601,
	LIBMODI_CODEPAGE_ISO_8859_13			= 28603,
	LIBMODI_CODEPAGE_ISO_8859_14			= 28604,
	LIBMODI_CODEPAGE_ISO_8859_15			= 28605,
	LIBMODI_CODEPAGE_ISO_8859_16			= 28606,

	LIBMODI_CODEPAGE_KOI8_R				= 20866,
	LIBMODI_CODEPAGE_KOI8_U				= 21866,

	LIBMODI_CODEPAGE_WINDOWS_874			= 874,
	LIBMODI_CODEPAGE_WINDOWS_932			= 932,
	LIBMODI_CODEPAGE_WINDOWS_936			= 936,
	LIBMODI_CODEPAGE_WINDOWS_949			= 949,
	LIBMODI_CODEPAGE_WINDOWS_950			= 950,
	LIBMODI_CODEPAGE_WINDOWS_1250			= 1250,
	LIBMODI_CODEPAGE_WINDOWS_1251			= 1251,
	LIBMODI_CODEPAGE_WINDOWS_1252			= 1252,
	LIBMODI_CODEPAGE_WINDOWS_1253			= 1253,
	LIBMODI_CODEPAGE_WINDOWS_1254			= 1254,
	LIBMODI_CODEPAGE_WINDOWS_1255			= 1255,
	LIBMODI_CODEPAGE_WINDOWS_1256			= 1256,
	LIBMODI_CODEPAGE_WINDOWS_1257			= 1257,
	LIBMODI_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBMODI_CODEPAGE_US_ASCII			LIBMODI_CODEPAGE_ASCII

#define LIBMODI_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBMODI_CODEPAGE_ISO_8859_1
#define LIBMODI_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBMODI_CODEPAGE_ISO_8859_2
#define LIBMODI_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBMODI_CODEPAGE_ISO_8859_3
#define LIBMODI_CODEPAGE_ISO_NORTH_EUROPEAN		LIBMODI_CODEPAGE_ISO_8859_4
#define LIBMODI_CODEPAGE_ISO_CYRILLIC			LIBMODI_CODEPAGE_ISO_8859_5
#define LIBMODI_CODEPAGE_ISO_ARABIC			LIBMODI_CODEPAGE_ISO_8859_6
#define LIBMODI_CODEPAGE_ISO_GREEK			LIBMODI_CODEPAGE_ISO_8859_7
#define LIBMODI_CODEPAGE_ISO_HEBREW			LIBMODI_CODEPAGE_ISO_8859_8
#define LIBMODI_CODEPAGE_ISO_TURKISH			LIBMODI_CODEPAGE_ISO_8859_9
#define LIBMODI_CODEPAGE_ISO_NORDIC			LIBMODI_CODEPAGE_ISO_8859_10
#define LIBMODI_CODEPAGE_ISO_THAI			LIBMODI_CODEPAGE_ISO_8859_11
#define LIBMODI_CODEPAGE_ISO_BALTIC			LIBMODI_CODEPAGE_ISO_8859_13
#define LIBMODI_CODEPAGE_ISO_CELTIC			LIBMODI_CODEPAGE_ISO_8859_14

#define LIBMODI_CODEPAGE_ISO_LATIN_1			LIBMODI_CODEPAGE_ISO_8859_1
#define LIBMODI_CODEPAGE_ISO_LATIN_2			LIBMODI_CODEPAGE_ISO_8859_2
#define LIBMODI_CODEPAGE_ISO_LATIN_3			LIBMODI_CODEPAGE_ISO_8859_3
#define LIBMODI_CODEPAGE_ISO_LATIN_4			LIBMODI_CODEPAGE_ISO_8859_4
#define LIBMODI_CODEPAGE_ISO_LATIN_5			LIBMODI_CODEPAGE_ISO_8859_9
#define LIBMODI_CODEPAGE_ISO_LATIN_6			LIBMODI_CODEPAGE_ISO_8859_10
#define LIBMODI_CODEPAGE_ISO_LATIN_7			LIBMODI_CODEPAGE_ISO_8859_13
#define LIBMODI_CODEPAGE_ISO_LATIN_8			LIBMODI_CODEPAGE_ISO_8859_14
#define LIBMODI_CODEPAGE_ISO_LATIN_9			LIBMODI_CODEPAGE_ISO_8859_15
#define LIBMODI_CODEPAGE_ISO_LATIN_10			LIBMODI_CODEPAGE_ISO_8859_16

#define LIBMODI_CODEPAGE_KOI8_RUSSIAN			LIBMODI_CODEPAGE_KOI8_R
#define LIBMODI_CODEPAGE_KOI8_UKRAINIAN			LIBMODI_CODEPAGE_KOI8_U

#define LIBMODI_CODEPAGE_WINDOWS_THAI			LIBMODI_CODEPAGE_WINDOWS_874
#define LIBMODI_CODEPAGE_WINDOWS_JAPANESE		LIBMODI_CODEPAGE_WINDOWS_932
#define LIBMODI_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBMODI_CODEPAGE_WINDOWS_936
#define LIBMODI_CODEPAGE_WINDOWS_KOREAN			LIBMODI_CODEPAGE_WINDOWS_949
#define LIBMODI_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBMODI_CODEPAGE_WINDOWS_950
#define LIBMODI_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBMODI_CODEPAGE_WINDOWS_1250
#define LIBMODI_CODEPAGE_WINDOWS_CYRILLIC		LIBMODI_CODEPAGE_WINDOWS_1251
#define LIBMODI_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBMODI_CODEPAGE_WINDOWS_1252
#define LIBMODI_CODEPAGE_WINDOWS_GREEK			LIBMODI_CODEPAGE_WINDOWS_1253
#define LIBMODI_CODEPAGE_WINDOWS_TURKISH		LIBMODI_CODEPAGE_WINDOWS_1254
#define LIBMODI_CODEPAGE_WINDOWS_HEBREW			LIBMODI_CODEPAGE_WINDOWS_1255
#define LIBMODI_CODEPAGE_WINDOWS_ARABIC			LIBMODI_CODEPAGE_WINDOWS_1256
#define LIBMODI_CODEPAGE_WINDOWS_BALTIC			LIBMODI_CODEPAGE_WINDOWS_1257
#define LIBMODI_CODEPAGE_WINDOWS_VIETNAMESE		LIBMODI_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_CODEPAGE_H ) */

