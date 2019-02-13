require "./globs/*"
require "string_scanner"

# Expands glob-like strings into array sets.
#
# If you've ever seen a string like this:
#
#     hostname.{west, east, north}.{100..150}.com
#
# ...and wished that there were a way to have that expand to all 153 urls without
# having to type out a bunch of arbitrarily deep map statements this gem is for you.
#
# Why is this handy? If you have to type out a whole load of AWS names this can
# be a lot nicer to type and iterate over to perform actions.
module Globs
  VERSION = "0.1.0"

  # Shorthand for `puts expand(str)` for outputting to STDOUT for
  # unix-like piping.
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
