/**
 * @file
 * Test code for Two-char Expando Render
 *
 * @authors
 * Copyright (C) 2023-2024 Tóth János <gomba007@gmail.com>
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

#define TEST_NO_MAIN
#include "config.h"
#include "acutest.h"
#include <stdio.h>
#include "mutt/lib.h"
#include "expando/lib.h"
#include "common.h" // IWYU pragma: keep
#include "test_common.h"

struct SimpleData
{
  const char *s;
  int d;
};

static void simple_ss(const struct ExpandoNode *node, void *data,
                      MuttFormatFlags flags, struct Buffer *buf)
{
  ASSERT(node->type == ENT_EXPANDO);

  const struct SimpleData *sd = data;

  const char *s = NONULL(sd->s);
  buf_strcpy(buf, s);
}

static void simple_dd(const struct ExpandoNode *node, void *data,
                      MuttFormatFlags flags, struct Buffer *buf)
{
  ASSERT(node->type == ENT_EXPANDO);

  const struct SimpleData *sd = data;

  const int num = sd->d;
  buf_printf(buf, "%d", num);
}

void test_expando_two_char_expando_render(void)
{
  const char *input = "%ss - %dd";

  const struct ExpandoDefinition defs[] = {
    { "ss", NULL, 1, 0, NULL },
    { "dd", NULL, 1, 1, NULL },
    { NULL, NULL, 0, 0, NULL },
  };

  struct Buffer *err = buf_pool_get();
  struct Expando *exp = expando_parse(input, defs, err);
  TEST_CHECK(exp != NULL);
  TEST_CHECK(buf_is_empty(err));

  check_node_expando(node_get_child(exp->node, 0), NULL, NULL);
  check_node_text(node_get_child(exp->node, 1), " - ");
  check_node_expando(node_get_child(exp->node, 2), NULL, NULL);

  const char *expected = "Test2 - 12";

  const struct ExpandoRenderCallback render[] = {
    { 1, 0, simple_ss },
    { 1, 1, simple_dd },
    { -1, -1, NULL },
  };

  struct SimpleData data = {
    .s = "Test2",
    .d = 12,
  };

  struct Buffer *buf = buf_pool_get();
  expando_render(exp, render, &data, MUTT_FORMAT_NO_FLAGS, buf->dsize, buf);

  TEST_CHECK_STR_EQ(buf_string(buf), expected);

  expando_free(&exp);
  buf_pool_release(&err);
  buf_pool_release(&buf);
}
