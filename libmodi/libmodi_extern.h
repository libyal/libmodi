/*
 * The internal extern definition
 *
 * Copyright (C) 2012-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBMODI_INTERNAL_EXTERN_H )
#define _LIBMODI_INTERNAL_EXTERN_H

#include <common.h>

/* Define HAVE_LOCAL_LIBMODI for local use of libmodi
 */
#if !defined( HAVE_LOCAL_LIBMODI )

#include <libmodi/extern.h>

#define LIBMODI_EXTERN_VARIABLE	LIBMODI_EXTERN

#else
#define LIBMODI_EXTERN		/* extern */
#define LIBMODI_EXTERN_VARIABLE	extern

#endif /* !defined( HAVE_LOCAL_LIBMODI ) */

#endif /* !defined( _LIBMODI_INTERNAL_EXTERN_H ) */

