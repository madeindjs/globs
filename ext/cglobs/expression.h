#ifndef EXPRESSION_H
#define EXPRESSION_H

/**
 * Search all matching string with a given REGEX
 *
 * @see https://gist.github.com/ianmackinnon/3294587
 * @param  source      the string to search
 * @return             status
 */
int get_group(const char *source, VALUE *ruby_array);

/**
 * Search all matching string with a given REGEX
 *
 * @see https://gist.github.com/ianmackinnon/3294587
 * @param  source      the string to search
 * @param  regexString a valid REGEX string
 * @return             status
 */
int get_matches(const char *source, const char *regexString, VALUE *ruby_array);

#endif
