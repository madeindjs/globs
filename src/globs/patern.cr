require "string_scanner"

module Globs
  class Patern
    def initialize(@content : String)
    end

    def expand : Array(String)
      if @content.includes?(Globs::PATERN_SEPARATOR)
        return @content.split(Globs::PATERN_SEPARATOR).map { |subpatern| subpatern.strip }
      else
        return [@content]
      end
    end
  end
end
