#include <ruby.h>

VALUE rb_cprint(VALUE self, VALUE str) {
  if (RB_TYPE_P(str, T_STRING) == 1) {
    return rb_sprintf("Printed from C code: %ld", str);
  }
  return Qnil;
}

void Init_cglobs() {
  VALUE mod = rb_define_module("Globs");
  printf("hello from C\n");
  rb_define_singleton_method(mod, "cprint", rb_cprint, 1);
}
