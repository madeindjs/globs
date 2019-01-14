require 'mkmf'

EXTENSION_NAME = 'cglobs'.freeze

have_header 'regex'

# $srcs = ['ext/cglobs/lib/expression.c']

dir_config(EXTENSION_NAME)
create_makefile EXTENSION_NAME
