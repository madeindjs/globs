require "string_scanner"

module Globs
  class Sentence
    def initialize(@content : String)
    end

    def expand : Array(String)
      scanner = StringScanner.new(@content)

      first = scanner.scan_until(Globs::OPENING_BRACE)
      patern = scanner.scan_until(Globs::CLOSING_BRACE)

      if patern.is_a? String
        complete_patern = "#{patern}#{Globs::CLOSING_BRACE_CHAR}"
        patern = patern.chomp(Globs::CLOSING_BRACE_CHAR)
        return Patern.new(patern).expand.map { |expand|
          @content.gsub(complete_patern, expand)
        }
      end

      return [@content]
    end
  end
end
