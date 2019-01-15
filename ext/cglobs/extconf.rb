require 'mkmf'

EXTENSION_NAME = 'cglobs'.freeze

dir_config(EXTENSION_NAME)
create_makefile EXTENSION_NAME
