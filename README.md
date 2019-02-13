# Globs

Expands glob-like strings into array sets.

> This a Crystal version of [baweaver/globs](https://github.com/baweaver/globs) initially written in Ruby.

If you've ever seen a string like this:

    hostname.{west, east, north}.{100..150}.com

...and wished that there were a way to have that expand to all 153 urls without having to type out a bunch of arbitrarily deep map statements this shards is for you.

Why is this handy? If you have to type out a whole load of AWS names this can be a lot nicer to type and iterate over to perform actions.

## Expressions

### Sets

## Usage

A set is defined as a set of comma delimited items inside brackets:

    {1, 2, 3}

In Globs, this would expand to the array `[1, 2, 3]`. The difference is if there happen to be multiple globs present it will expand those items:

~~~crystal
Globs.expand("test.{a, b}.{1, 2}.com")
=> ["test.a.1.com", "test.a.2.com", "test.b.1.com", "test.b.2.com"]
~~~

These sets can be as long or as short as you would like.

### Ranges

Use inclusive (`..`) ranges to shorten consecutive elements in a Globs string:

~~~crystal
Globs.expand("test.{a..e}.com")
=> ["test.a.com", "test.b.com", "test.c.com", "test.d.com", "test.e.com"]
~~~

## Instalation

### Librairy

1. Add the dependency to your `shard.yml`:

~~~yaml
dependencies:
 lapp:
   github: madeindjs/glob
~~~

2. Run `shards install`

### CLI

Clone and compile yoursel

~~~bash
$ git clone https://github.com/madeindjs/globs
$ cd globs
$ crystal build bin/globs.cr --release
~~~

Then you can simply use like this:

~~~bash
$ ./globs "http://{a,b}.{1..3}.org"
http://a.1.org
http://a.2.org
http://a.3.org
http://b.1.org
http://b.2.org
http://b.3.org
~~~

## Contributing

1. Fork it (<https://github.com/madeindjs/globs/fork>)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

## Contributors

- [Alexandre Rousseau](https://github.com/madeindjs) - creator and maintainer

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
