#include <ruby.h>

#include <regex.h>

#include "expression.h"

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
