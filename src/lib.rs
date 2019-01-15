extern crate regex;
use regex::Regex;

/// Expand the given string and return all possibles strings
pub fn expands(expandable: &str) -> Vec<String> {
    let mut expands: Vec<String> = Vec::new();

    let re: Regex = Regex::new(r"\{(([A-z]+,?)+)\}").unwrap();

    if !re.is_match(expandable) {
        expands.push(expandable.to_string());
    }

    for cap in re.captures_iter(expandable) {
        let group: &str = &cap[0];
        let group_without_brackets: &str = &cap[1];

        for item in expands_group(group_without_brackets) {
            let expand: String = expandable.replace(group, item);
            expands.push(expand);
        }
    }

    return expands;
}

fn expands_group(group_without_brackets: &str) -> Vec<&str> {
    group_without_brackets.split(",").collect()
}

#[cfg(test)]
mod tests {
    #[test]
    fn without_any_group() {
        assert_eq!(vec!["Hello"], super::expands("Hello"));
    }

    #[test]
    fn with_a_simple_group() {
        let input = "https://{qwant,duckduckgo,startpage}.com/";
        let expected = vec![
            "https://qwant.com/",
            "https://duckduckgo.com/",
            "https://startpage.com/",
        ];

        assert_eq!(expected, super::expands(input));
    }
}
