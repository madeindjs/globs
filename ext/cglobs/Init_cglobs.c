#include <regex.h>
#include <ruby.h>
#include <string.h>

const char OPENING_BRACE = '{';
const char CLOSING_BRACE = '}';

/**
 * @see https://gist.github.com/ianmackinnon/3294587
 * @return [description]
 */
int get_matches() {
  char *source = "___ abc123def ___ ghi456 ___";
  char *regexString = "[a-z]*([0-9]+)([a-z]*)";
  size_t maxMatches = 2;
  size_t maxGroups = 3;

  regex_t regexCompiled;
  regmatch_t groupArray[maxGroups];
  unsigned int m;
  char *cursor;

  if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
    printf("Could not compile regular expression.\n");
    return 1;
  };

  m = 0;
  cursor = source;
  for (m = 0; m < maxMatches; m++) {
    if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
      break; // No more matches

    unsigned int g = 0;
    unsigned int offset = 0;
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

  return 0;
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

  get_matches();

  // return an empty array if not a string
  if (RB_TYPE_P(str, T_STRING) != 1) {
    return array;
  }

  // extract string value from VALUE
  char *str_value = RSTRING_PTR(str);

  regex_t regex;
  int reti;
  char msgbuf[100];

  /* Compile regular expression */
  reti = regcomp(&regex, "^a[[:alnum:]]", 0);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  /* Execute regular expression */
  reti = regexec(&regex, str_value, 0, NULL, 0);
  if (!reti) {
    puts("Match");
  } else if (reti == REG_NOMATCH) {
    puts("No match");
  } else {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    exit(1);
  }

  // Free memory allocated to the pattern buffer by regcomp()
  regfree(&regex);

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
  printf("hello from C\n");
  rb_define_singleton_method(mod, "expands_c", rb_globs_expand, 1);
}
