require "string_scanner"

module Globs
  # A Patern is a group (ex: `1,2,3`) or a range (ex: `1..3`) who can be expandes into an `Array(String)`
  class Patern
    # Represent a separator for group `Patern` (ex: `1,2,3`)
    GROUP_SEPARATOR = ','
    # Represent a separator for range `Patern` (ex: `1...3`)
    RANGE_SEPARATOR = ".."

    def initialize(@content : String)
    end

    # Get all possibilities of this patern
    def expand : Array(String)
      if @content.includes?(GROUP_SEPARATOR)
        return @content.split(GROUP_SEPARATOR).map { |subpatern| subpatern.strip }
      elsif @content.includes?(RANGE_SEPARATOR)
        range_items = @content.split(RANGE_SEPARATOR)
        return Range.new(range_items.first, range_items.last).to_a
      else
        return [@content]
      end
    end
  end
end
