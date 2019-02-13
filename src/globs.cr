require "./globs/*"
require "string_scanner"

module Globs
  VERSION = "0.1.0"

  # Opening brace of a Glob expression
  OPENING_BRACE      = /\{/
  OPENING_BRACE_CHAR = '{'

  # Closing brace of a Glob expression
  CLOSING_BRACE      = /\}/
  CLOSING_BRACE_CHAR = '}'

  PATERN_SEPARATOR = ','

  # Shorthand for `puts expand(str)` for outputting to STDOUT for
  # unix-like piping.
  #
  # @since 0.0.2
  #
  # @param string [String]
  #   Glob-like string to be expanded
  #
  # @return [NilClass]
  #   Only outputs to STDOUT, returning `nil` from the actual
  #   method call
  def puts(string : String)
    puts self.expand(string)
  end

  # Expands a glob-like string into all possible interpretations of it.
  def self.expand(string : String) : Array
    return Sentence.new(string).expand
  end
end
