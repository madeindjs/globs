require "../src/globs"

require "option_parser"

# parse new values
parsed = OptionParser.parse! do |p|
  p.banner = <<-STRING
  Glob
  ====
  author: Alexandre Rousseau <contact@rousseau-alexandre.fr>
  version: #{Globs::VERSION}

  Usage: glob <expresion>"
  STRING

  p.on("-h", "--help", "Show this help") { puts p; exit }
  p.invalid_option do |flag|
    STDERR.puts "ERROR: #{flag} is not a valid option."
    STDERR.puts p
    exit(1)
  end
end

expression = ARGV.pop?

if expression.nil?
  STDERR.puts "ERROR: Please enter an expression."
  STDERR.puts parsed
  exit(1)
end

Globs.expand(expression).each do |expand|
  puts expand
end
