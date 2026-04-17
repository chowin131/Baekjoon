use std::io::{self, BufRead, BufWriter, Write};
fn main() {
    let stdin = io::stdin();
    let mut reader = stdin.lock();
    let stdout = io::stdout();
    let mut writer = BufWriter::new(stdout.lock());
    let mut line = String::new();
    reader.read_line(&mut line).unwrap();
    let n: usize = line.trim().parse().unwrap();
    for _ in 0..n {
        line.clear();
        reader.read_line(&mut line).unwrap();
        let words: Vec<&str> = line.split_whitespace().collect();
        if words.len() >= 3 {
            let tail = words[2..].join(" ");
            let head = words[0..2].join(" ");
            writeln!(writer, "{} {}", tail, head).unwrap();
        }
    }
}