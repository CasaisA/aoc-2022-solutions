//use std::fs;
use std::time;
pub fn oneliner() {
    let result = include_str!("../input.txt")
        .trim()
        .split("\n\n")
        .map(|e| {
            e.split("\n")
                .map(|f| f.parse::<i32>().unwrap())
                .sum::<i32>()
        })
        .max()
        .unwrap();
    println!("{result}");
}
pub fn mysolution()-> i32 {
    //let dwarfs = fs::read_to_string("./input.txt").unwrap();
    //dwarfs.trim().split("\n\n");
    let dwarfs = include_str!("../input.txt").trim().split("\n\n"); //.collect::<Vec<&str>>();
    let mut highest: i32 = -1;

    for dwarf in dwarfs {
        let mut food_calories: i32 = 0;
        let food = dwarf.split("\n"); //.collect::<Vec<&str>>();
        for f in food {
            food_calories += f.parse::<i32>().unwrap();
        }
        if food_calories > highest {
            highest = food_calories;
        }
    }
    highest
}
pub fn main() {
    println!("Entering!");
    let now = time::Instant::now();
    let highest = mysolution();
    let mut time = now.elapsed().as_nanos();
    println!("Highest calories {highest}. In {time} s");
    let new_now = time::Instant::now();
    oneliner();
    time = new_now.elapsed().as_nanos();
    println!("One liner takes {time} s");
}
