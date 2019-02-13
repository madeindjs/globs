require "./spec_helper"

describe Globs::Patern do
  it "expand a group definition" do
    Globs::Patern.new("a, b, c").expand.should eq(%w(a b c))
  end

  it "expand a range definition" do
    Globs::Patern.new("1..4").expand.should eq(%w(1 2 3 4))
  end
end
