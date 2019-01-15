mod lib;

fn main() {
    let expands: Vec<String> = lib::expands("https://{qwant,duckduckgo,startpage}.com/");

    for item in expands {
        println!("{}", item);
    }
}
