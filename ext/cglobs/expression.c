#include <regex.h>
#include <ruby.h>

#include "expression.h"
#define MAX_MATCHES 2
#define MAX_GROUPS 3

int get_group(const char *source, VALUE *ruby_array) {
  get_matches(source, "(.*)\\{(.*)\\}(.*)", ruby_array);
  return EXIT_SUCCESS;
}

int get_matches(const char *source, const char *regexString,
                VALUE *ruby_array) {
  unsigned int group_index, match_index = 0;

  long long offset = 0;

  regex_t compiled_regex;
  regmatch_t groups_array[MAX_GROUPS];
  char *cursor;

  // compile REGEX
  if (regcomp(&compiled_regex, regexString, REG_EXTENDED)) {
    printf("Could not compile regular expression.\n");
    printf("Could not compile regular expression.\n");
    return EXIT_FAILURE;
  };

  cursor = source;
  for (match_index = 0; match_index < MAX_MATCHES; match_index++) {
    if (regexec(&compiled_regex, cursor, MAX_GROUPS, groups_array, 0)) {
      printf("No more matches.\n");
      break; // No more matches
    }

    for (group_index = 0; group_index < MAX_GROUPS; group_index++) {
      regmatch_t group_regmatch = groups_array[group_index];

      if (group_regmatch.rm_so == (size_t)-1)
        break; // No more groups

      if (group_index == 0) {
        offset = group_regmatch.rm_eo;
      }

      char cursor_copy[strlen(cursor) + 1];
      strcpy(cursor_copy, cursor);
      cursor_copy[group_regmatch.rm_eo] = 0;

      char *matched_string = cursor_copy + group_regmatch.rm_so;

      printf("Match %u, Group %u: [%2u-%2u]: %s\n", match_index, group_index,
             group_regmatch.rm_so, group_regmatch.rm_eo, matched_string);

      VALUE str_value_str = rb_str_new2(matched_string);
      rb_ary_push(ruby_array, str_value_str);
    }
    cursor += offset;
  }

  regfree(&compiled_regex);

  return EXIT_SUCCESS;
}
