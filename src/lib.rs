extern crate regex;
use regex::Regex;

/// Expand the given string and return all possibles strings
pub fn expands(expandable: &str) -> Vec<String> {
    let mut expands: Vec<String> = Vec::new();

    let re: Regex = Regex::new(r"\{(([A-z]+,?)+)\}").unwrap();

    println!(
        "Expands '{}' match ?: {}",
        expandable,
        re.is_match(expandable)
    );

    for cap in re.captures_iter(expandable) {
        println!("Month: {}", &cap[0]);
    }

    expands.push(expandable.to_string());

    return expands;
}

#[cfg(test)]
mod tests {
    #[test]
    fn without_any_group() {
        assert_eq!(vec!["Hello"], super::expands("Hello"));
    }

    #[test]
    fn no_matches() {
        let input = "https://{qwant,duckduckgo}.com/";
        let expected = vec!["https://qwant.com/", "https://duckduckgo.com/"];

        assert_eq!(expected, super::expands(input));
    }
}
