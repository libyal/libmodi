/*
 * Meta data functions
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

#if !defined( _LIBMODI_METADATA_H )
#define _LIBMODI_METADATA_H

#include <common.h>
#include <types.h>

#include "libmodi_extern.h"
#include "libmodi_libcerror.h"
#include "libmodi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBMODI_EXTERN \
int libmodi_handle_get_media_size(
     libmodi_handle_t *handle,
     size64_t *media_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMODI_METADATA_H ) */

