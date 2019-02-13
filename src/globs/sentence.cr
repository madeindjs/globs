require "string_scanner"

module Globs
  # A stentence is a text who contains (or not) somes `Patern`'s to expands
  class Sentence
    def initialize(@content : String)
    end

    # Get all possibilities of this setence and expands all containing `Patern`'s
    def expand : Array(String)
      scanner = StringScanner.new(@content)

      first = scanner.scan_until(Globs::OPENING_BRACE)
      patern = scanner.scan_until(Globs::CLOSING_BRACE)

      if patern.is_a? String
        complete_patern = "#{Globs::OPENING_BRACE_CHAR}#{patern}"
        patern = patern.chomp(Globs::CLOSING_BRACE_CHAR)
        return Patern.new(patern).expand.map { |expand|
          @content.gsub(complete_patern, expand)
        }
      end

      return [@content]
    end
  end
end
