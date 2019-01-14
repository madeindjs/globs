require 'mkmf'

EXTENSION_NAME = 'cglobs'.freeze

have_header 'regex'

# $srcs = ['lib/expression.c']

dir_config(EXTENSION_NAME)
create_makefile EXTENSION_NAME
