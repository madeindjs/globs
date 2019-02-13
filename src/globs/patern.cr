require "string_scanner"

module Globs
  # A Patern is a group (ex: `1,2,3`) or a range (ex: `1..3`) who can be expandes into an `Array(String)`
  class Patern
    def initialize(@content : String)
    end

    # Get all possibilities of this patern
    def expand : Array(String)
      if @content.includes?(Globs::GROUP_SEPARATOR)
        return @content.split(Globs::GROUP_SEPARATOR).map { |subpatern| subpatern.strip }
      elsif @content.includes?(Globs::RANGE_SEPARATOR)
        range_items = @content.split(Globs::RANGE_SEPARATOR)
        return Range.new(range_items.first, range_items.last).to_a
      else
        return [@content]
      end
    end
  end
end
