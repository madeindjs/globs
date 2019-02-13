require "string_scanner"

module Globs
  # A Patern is a group (ex: `1,2,3`) or a range (ex: `1..3`) who can be expandes into an `Array(String)`
  class Patern
    # Represent a separator for group `Patern` (ex: `1,2,3`)
    GROUP_SEPARATOR = ','
    # Represent a separator for range `Patern` (ex: `1...3`)
    RANGE_SEPARATOR = ".."

    def initialize(@conten : String)
      @content_brace = "#{Sentence::OPENING_BRACE_CHAR}#{@conten}#{Sentence::CLOSING_BRACE_CHAR}"
    end

    # Get all possibilities of this patern
    def expand : Array(String)
      content = @conten.chomp(Sentence::CLOSING_BRACE_CHAR)

      if content.includes?(GROUP_SEPARATOR)
        return content.split(GROUP_SEPARATOR).map { |subpatern| subpatern.strip }
      elsif content.includes?(RANGE_SEPARATOR)
        range_items = content.split(RANGE_SEPARATOR)
        return Range.new(range_items.first, range_items.last).to_a
      else
        return [content]
      end
    end

    def replace(sentence : String) : Array(String)
      self.expand.map { |expand|
        sentence.gsub(@content_brace, expand)
      }
    end
  end
end
