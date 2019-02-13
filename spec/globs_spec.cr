require "./spec_helper"

describe Globs do
  it "has a version number" do
    # expect(Globs::VERSION).not_to be nil
  end

  it "does not expand a normal string" do
    Globs.expand("a_normal_string").should eq(%w(a_normal_string))
  end

  it "can expand a single group set" do
    Globs.expand("test.{a, b, c}.com").should eq(%w(
      test.a.com
      test.b.com
      test.c.com
    ))
  end

  it "can expand a single range set" do
    Globs.expand("test.{1..3}.com").should eq(%w(
      test.1.com
      test.2.com
      test.3.com
    ))
  end

  it "can expand multiple sets" do
    Globs.expand("test.{a, b, c}.{1, 2}.com").should eq(%w(
      test.a.1.com
      test.a.2.com
      test.b.1.com
      test.b.2.com
      test.c.1.com
      test.c.2.com
    ))
  end

  it "can expand a range" do
    Globs.expand("test.{a..c}.{1, 2}.com").should eq(%w(
      test.a.1.com
      test.a.2.com
      test.b.1.com
      test.b.2.com
      test.c.1.com
      test.c.2.com
    ))
  end
end
