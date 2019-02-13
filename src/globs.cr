require "./globs/patern"
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
    puts expand(string)
  end

  # Expands a glob-like string into all possible interpretations of it.
  def self.expand(string : String) : Array
    (String)
    scanner = StringScanner.new(string)

    first = scanner.scan_until(OPENING_BRACE)
    patern = scanner.scan_until(CLOSING_BRACE)

    if patern.is_a? String
      patern = patern.chomp(CLOSING_BRACE_CHAR)
      complete_patern = "#{OPENING_BRACE_CHAR}#{patern}#{CLOSING_BRACE_CHAR}"
      return Patern.new(patern).expand.map { |expand|
        string.gsub(complete_patern, expand)
      }
    end

    # scanner = StringScanner.new(string)
    return [string]
  end

  private def self.expand_patern(patern : String) : Array(String)
    if patern.includes?(PATERN_SEPARATOR)
      return patern.split(PATERN_SEPARATOR).map { |subpatern| subpatern.strip }
    else
      return [patern]
    end
  end
end
