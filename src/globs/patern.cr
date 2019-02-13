require "string_scanner"

module Globs
  class Patern
    def initialize(@content : String)
    end

    def expand : Array(String)
      if @content.includes?(Globs::PATERN_SEPARATOR)
        return @content.split(Globs::PATERN_SEPARATOR).map { |subpatern| subpatern.strip }
      elsif @content.includes?(Globs::RANGE_SEPARATOR)
        range_items = @content.split(Globs::RANGE_SEPARATOR)
        return Range.new(range_items.first, range_items.last).to_a
      else
        return [@content]
      end
    end
  end
end
