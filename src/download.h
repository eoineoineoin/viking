/*
 * viking -- GPS Data and Topo Analyzer, Explorer, and Manager
 *
 * Copyright (C) 2003-2005, Evan Battaglia <gtoevan@gmx.net>
 * Copyright (C) 2007, Guilhem Bonnefille <guilhem.bonnefille@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef _VIKING_DOWNLOAD_H
#define _VIKING_DOWNLOAD_H

#include <stdio.h>

G_BEGIN_DECLS

/* File content check */
typedef gboolean (*VikFileContentCheckerFunc) (FILE*);
gboolean a_check_map_file(FILE*);
gboolean a_check_html_file(FILE*);
gboolean a_check_kml_file(FILE*);
// Convert
void a_try_decompress_file (gchar *name);
typedef void (*VikFileContentConvertFunc) (gchar*); // filename (temporary)

#define ONE_WEEK_SECS 604800

typedef struct {
  /**
   * Check if the server has a more recent file than the one we have before downloading it
   * This uses http header If-Modified-Since
   */
  gboolean check_file_server_time;

  /**
   * Set if the server handle ETag
   */
  gboolean use_etag;

  /**
   * The REFERER string to use.
   * Could be NULL.
   */
  gchar *referer;

  /**
   * follow_location specifies the number of retries
   * to follow a redirect while downloading a page.
   */
  glong follow_location;

  /**
   * Use the specified user_agent in the request
   * Could be NULL.
   * When defined this is used in preference to the curl_user_agent
   */
  gchar *user_agent;

  /**
   * Custom http headers in the send request.
   * Separate multiple requests with '\n'
   */
  gchar *custom_http_headers;

  /**
   * File expiry age in seconds, for (re)downloading an existing file - typically tiles.
   * This previously was global preference "download_tile_age" but now can be specified
   *  as necessary thus differing map layers can have different check periods.
   * Although this type allows setting to 0 (which is fine when downloading to a temporary file),
   *  the practical default should be 7 days (ONE_WEEK_SECS)
   *  and otherwise limited via the user interface to prevent use of 0 (e.g. ensure minimum 1 day).
   */
  guint expiry_age;

  /**
   * File content checker.
   */
  VikFileContentCheckerFunc check_file;

  /**
   * If need to authenticate on download
   *  format: 'username:password'
   */
  gchar *user_pass;

  /**
   * https://curl.se/libcurl/c/CURLOPT_UNRESTRICTED_AUTH.html
   * Send credentials to other hosts too
   */
  gboolean allow_credential_follow;

  /**
   * ATM a single cookie jar is used between all connections that desire cookie usage
   */
  gboolean use_cookies;

  /**
   * File manipulation if necessary such as uncompressing the downloaded file.
   */
  VikFileContentConvertFunc convert_file;

} DownloadFileOptions;

void a_download_file_options_free ( DownloadFileOptions *dfo );

void a_download_init(void);
void a_download_uninit(void);

typedef enum {
  DOWNLOAD_PARAMETERS_ERROR = -8, // Configuration issue
  DOWNLOAD_FILE_WRITE_ERROR = -4, // Can't write downloaded file :(
  DOWNLOAD_HTTP_ERROR = -2,
  DOWNLOAD_CONTENT_ERROR = -1,
  DOWNLOAD_SUCCESS = 0,
  DOWNLOAD_NOT_REQUIRED = 1, // Also 'successful'. e.g. Because file already exists and no time checks used
} DownloadResult_t;

/* TODO: convert to Glib */
DownloadResult_t a_http_download_get_url ( const char *hostname, const char *uri, const char *fn, DownloadFileOptions *opt, void *handle );
DownloadResult_t a_ftp_download_get_url ( const char *hostname, const char *uri, const char *fn, DownloadFileOptions *opt, void *handle );
void *a_download_handle_init ();
void a_download_handle_cleanup ( void *handle );

gchar *a_download_uri_to_tmp_file ( const gchar *uri, DownloadFileOptions *options );

G_END_DECLS

#endif
