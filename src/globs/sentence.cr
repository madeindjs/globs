require "string_scanner"

module Globs
  # A stentence is a text who contains (or not) somes `Patern`'s to expands
  class Sentence
    # A REGEX to find a beginning of a `Patern`
    OPENING_BRACE = /\{/
    # A Char to find a beginning of a `Patern`
    OPENING_BRACE_CHAR = '{'
    # A REGEX to find an ending of a `Patern`
    CLOSING_BRACE = /\}/
    # A Char to find a ending of a `Patern`
    CLOSING_BRACE_CHAR = '}'

    content : String

    def initialize(@content : String)
    end

    # Get all possibilities of this setence and expands all containing `Patern`'s
    def expand : Array(String)
      scanner = StringScanner.new(@content)

      paterns = [] of Patern
      expands = [@content]

      until scanner.eos?
        first = scanner.scan_until(OPENING_BRACE)
        patern = scanner.scan_until(CLOSING_BRACE)

        break if patern.nil?

        if patern.is_a? String
          complete_patern = "#{OPENING_BRACE_CHAR}#{patern}"
          paterns << Patern.new(patern.chomp(CLOSING_BRACE_CHAR))
        end
      end

      paterns.each do |patern|
        expands = expands.map do |expand|
          patern.replace(expand)
        end.flatten
        # return Patern.new(patern).expand.map { |expand|
        # @content.gsub(complete_patern, expand)
        # }
      end

      return expands
    end

    private def walk_to_next_patern
    end
  end
end
