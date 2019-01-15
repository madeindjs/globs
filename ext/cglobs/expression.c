#include <ruby.h>
#include <string.h>

#include "expression.h"
#define MAX_MATCHES 2
#define MAX_GROUPS 3
#define OPENING_BRACE '{'
#define CLOSING_BRACE '}'

int expands(const char *source, VALUE ruby_array) {
  unsigned int i, source_length;
  char source_cursor;
  char *group;

  int opened_group;

  opened_group = 0;

  source_length = strlen(source);

  for (i = 0; i < source_length; i++) {
    source_cursor = source[i];

    if (source_cursor == OPENING_BRACE) {
      opened_group = 1;
    }

    if (opened_group == 1) {
      group_add_char(group, source_cursor);
      // strcat(group, source_cursor);
    }

    if (source_cursor == CLOSING_BRACE) {
      opened_group = 0;
      printf("%s\n", group);
    }
  }

  return EXIT_SUCCESS;
}

char *group_add_char(char *str, char c) {
  size_t len = strlen(str);
  // one for extra char, one for trailing zero
  char *str2 = malloc(len + 1 + 1);

  strcpy(str2, str);
  str2[len] = c;
  str2[len + 1] = '\0';

  return str2;
}
