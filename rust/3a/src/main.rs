use std::collections::HashMap;
pub(crate) use std::fs;

pub fn main() {
    let input = fs::read_to_string("./input.txt").expect("Ok");
    let input = input.trim();
    let games = input.split("\n").collect::<Vec<&str>>();

    let rps_map = HashMap::from([
        ("A", "R"),
        ("B", "P"),
        ("C", "S"),
        ("X", "R"),
        ("Y", "P"),
        ("Z", "S"),
    ]);
    let mut total_points = 0;
    for game in games {
        let players = game.split(" ").collect::<Vec<&str>>();
        let myplay = format!("{}", rps_map[players[1]]);
        let result = format!("{}{}", rps_map[players[0]],
                             myplay);
        println!("{result}");

        match result.as_ref() {
            "SR" | "RP" | "PS" => {
                total_points += 6;
                println!("You win!")
            }
            "RR" | "SS" | "PP" => {
                total_points += 3;
                println!("You draw!");
            }
            _ => println!("You lose!"),
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
