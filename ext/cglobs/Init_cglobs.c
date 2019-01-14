#include <regex.h>
#include <ruby.h>
#include <string.h>

const char OPENING_BRACE = '{';
const char CLOSING_BRACE = '}';

/**
 * @see https://gist.github.com/ianmackinnon/3294587
 * @return [description]
 */
int get_matches(const char *source, const char *regexString) {
  size_t maxMatches = 2;
  size_t maxGroups = 3;
  unsigned int g, m, offset;

  regex_t regexCompiled;
  regmatch_t groupArray[maxGroups];
  char *cursor;

  if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
    printf("Could not compile regular expression.\n");
    return EXIT_FAILURE;
  };

  m = 0;
  cursor = source;
  for (m = 0; m < maxMatches; m++) {
    if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0)) {
      printf("No more matches.\n");
      break; // No more matches
    }

    m = g = offset = 0;

    for (g = 0; g < maxGroups; g++) {
      if (groupArray[g].rm_so == (size_t)-1)
        break; // No more groups

      if (g == 0)
        offset = groupArray[g].rm_eo;

      char cursorCopy[strlen(cursor) + 1];
      strcpy(cursorCopy, cursor);
      cursorCopy[groupArray[g].rm_eo] = 0;
      printf("Match %u, Group %u: [%2u-%2u]: %s\n", m, g, groupArray[g].rm_so,
             groupArray[g].rm_eo, cursorCopy + groupArray[g].rm_so);
    }
    cursor += offset;
  }

  regfree(&regexCompiled);

  return EXIT_SUCCESS;
}

/**
 * Split a string
 *
 * @see
 * http://source-code-share.blogspot.com/2014/07/implementation-of-java-stringsplit.html
 *
 * @param  str the string to split
 * @param  c   the character to split
 * @param  arr an array containing results
 * @return     the number of splits
 */
int split(const char *str, char c, char ***arr) {
  int count = 1;
  int token_len = 1;
  int i = 0;
  char *p;
  char *t;

  p = str;
  while (*p != '\0') {
    if (*p == c)
      count++;
    p++;
  }

  *arr = (char **)malloc(sizeof(char *) * count);
  if (*arr == NULL)
    exit(1);

  p = str;
  while (*p != '\0') {
    if (*p == c) {
      (*arr)[i] = (char *)malloc(sizeof(char) * token_len);
      if ((*arr)[i] == NULL)
        exit(1);

      token_len = 0;
      i++;
    }
    p++;
    token_len++;
  }
  (*arr)[i] = (char *)malloc(sizeof(char) * token_len);
  if ((*arr)[i] == NULL)
    exit(1);

  i = 0;
  p = str;
  t = ((*arr)[i]);
  while (*p != '\0') {
    if (*p != c && *p != '\0') {
      *t = *p;
      t++;
    } else {
      *t = '\0';
      i++;
      t = ((*arr)[i]);
    }
    p++;
  }

  return count;
}

VALUE rb_globs_expand(VALUE self, VALUE str) {
  VALUE array = rb_ary_new();
  const char *str_value = RSTRING_PTR(str);

  get_matches("___ abc123def ___ ghi456 ___", "[a-z]*([0-9]+)([a-z]*)");

  // return an empty array if not a string
  if (RB_TYPE_P(str, T_STRING) != 1) {
    return array;
  }

  // extract string value from VALUE

  get_matches(str_value, ".*\\{(.*)\\}.*");

  return array;
}

// VALUE rb_globs_expand(VALUE self, VALUE str) {
//   VALUE array = rb_ary_new();
//
//   // return an empty array if not a string
//   if (RB_TYPE_P(str, T_STRING) != 1) {
//     return array;
//   }
//
//   int i;
//   int c = 0;
//   char **arr = NULL;
//
//   // extract string value from VALUE
//   char *str_value = RSTRING_PTR(str);
//
//   c = split(str_value, ',', &arr);
//   // printf("found %d tokens.\n", c);
//
//   // add explosion into the Ruby array
//   for (i = 0; i < c; i++) {
//     VALUE string_exploded = rb_str_new2(arr[i]);
//     rb_ary_push(array, string_exploded);
//   }
//
//   return array;
// }

/**
 * Add `Globs.expands_c` methods in Ruby
 */
void Init_cglobs() {
  VALUE mod = rb_define_module("Globs");
  rb_define_singleton_method(mod, "expands_c", rb_globs_expand, 1);
}
