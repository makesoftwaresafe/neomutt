/**
 * @file
 * Structure for managing a table of multibyte characters
 *
 * @authors
 * Copyright (C) 2017 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MUTT_MBTABLE_H
#define _MUTT_MBTABLE_H

/**
 * struct MbTable - multibyte character table
 *
 * Allows for direct access to the individual multibyte characters in a
 * string.  This is used for the FlagChars, FromChars, StatusChars and ToChars
 * option types.
 */
struct MbTable
{
  int len;             /**< number of characters */
  char **chars;        /**< the array of multibyte character strings */
  char *segmented_str; /**< each chars entry points inside this string */
  char *orig_str;
};

#endif /* _MUTT_MBTABLE_H */
