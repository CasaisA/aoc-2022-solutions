use std::collections::HashMap;
pub(crate) use std::fs;

pub fn main() {
    let input = fs::read_to_string("./input.txt").expect("Ok");
    let input = input.trim();
    let games = input.split("\n").collect::<Vec<&str>>();

    let their_play_map = HashMap::from([("A", "R"), ("B", "P"), ("C", "S")]);
    let winning_map = HashMap::from([("R", "S"), ("P", "R"), ("S", "P")]);
    let losing_map: HashMap<&str, &str> = winning_map
        .iter()
        .map(|(k, v)| (v.clone(), k.clone()))
        .collect();
    let mut total_points = 0;
    for game in games {
        let players = game.split(" ").collect::<Vec<&str>>();
        let their_play = their_play_map[players[0]];
        let strategy = players[1];
        let myplay: &str;
        match strategy.as_ref() {
            "Y" => myplay = their_play,
            "X" => myplay = winning_map[their_play],
            "Z" => myplay = losing_map[their_play],
            _ => myplay = "",
        }
        let result = format!("{} {}", their_play_map[players[0]], myplay);

        match result.as_ref() {
            "S R" | "R P" | "P S" => {
                total_points += 6;
            }
            "R R" | "S S" | "P P" => {
                total_points += 3;
            }
            _ => ()
        }
        match myplay.as_ref() {
            "R" => total_points += 1,
            "P" => total_points += 2,
            "S" => total_points += 3,
            _ => (),
        }
    }
    println!("Total points: {total_points}");
}
