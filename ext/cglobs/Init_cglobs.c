#include <ruby.h>

VALUE rb_globs_expand(VALUE self, VALUE str) {
  VALUE array = rb_ary_new();

  if (RB_TYPE_P(str, T_STRING) == 1) {
    rb_ary_push(array, str);
  }

  return array;
}

/**
 * Add `Globs.expands_c` methods in Ruby
 */
void Init_cglobs() {
  VALUE mod = rb_define_module("Globs");
  printf("hello from C\n");
  rb_define_singleton_method(mod, "expands_c", rb_globs_expand, 1);
}
