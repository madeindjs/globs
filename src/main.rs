mod lib;

fn main() {
    let expands: Vec<String> = lib::expands("Hello, world!");

    for item in expands {
        println!("{}", item);
    }
}
