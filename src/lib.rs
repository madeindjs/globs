/// Expand the given string and return all possibles strings
pub fn expands(expandable: &str) -> Vec<String> {
    let mut expands: Vec<String> = Vec::new();

    expands.push(expandable.to_string());

    return expands;
}

#[cfg(test)]
mod tests {
    #[test]
    fn no_matches() {
        assert_eq!(vec!["Hello"], super::expands("Hello"));
    }
}
