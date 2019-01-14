#include <ruby.h>

#include <regex.h>

#include "expression.h"

int get_group(const char *source, VALUE *ruby_array) {
  get_matches(source, "(.*)\\{(.*)\\}(.*)", ruby_array);
  return EXIT_SUCCESS;
}

int get_matches(const char *source, const char *regexString,
                VALUE *ruby_array) {
  size_t maxMatches = 2;
  size_t maxGroups = 3;
  unsigned int g, m, offset;

  regex_t regexCompiled;
  regmatch_t groupArray[maxGroups];
  char *cursor;

  if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
    printf("Could not compile regular expression.\n");
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
      regmatch_t group_regmatch = groupArray[g];

      if (group_regmatch.rm_so == (size_t)-1)
        break; // No more groups

      if (g == 0) {
        offset = group_regmatch.rm_eo;
      }

      char cursorCopy[strlen(cursor) + 1];
      strcpy(cursorCopy, cursor);
      cursorCopy[group_regmatch.rm_eo] = 0;

      char *matched_string = cursorCopy + group_regmatch.rm_so;

      printf("Match %u, Group %u: [%2u-%2u]: %s\n", m, g, group_regmatch.rm_so,
             group_regmatch.rm_eo, matched_string);

      VALUE str_value_str = rb_str_new2(matched_string);
      rb_ary_push(ruby_array, str_value_str);
    }
    cursor += offset;
  }

  regfree(&regexCompiled);

  return EXIT_SUCCESS;
}
