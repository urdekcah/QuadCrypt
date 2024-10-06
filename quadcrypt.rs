use std::io::{self, Write};

fn twoencrypt() {
  let mut input = String::new();
  print!("a : ");
  io::stdout().flush().unwrap();
  io::stdin().read_line(&mut input).unwrap();
  let ra: i32 = input.trim().parse().unwrap();

  input.clear();
  print!("b : ");
  io::stdout().flush().unwrap();
  io::stdin().read_line(&mut input).unwrap();
  let rb: i32 = input.trim().parse().unwrap();

  input.clear();
  print!("c : ");
  io::stdout().flush().unwrap();
  io::stdin().read_line(&mut input).unwrap();
  let rc: i32 = input.trim().parse().unwrap();

  input.clear();
  println!("Enter the string:");
  io::stdin().read_line(&mut input).unwrap();
  let strings = input.trim();

  let mut output = vec![];
  let a = ra + rb;
  let b = rb + rc;
  let c = rc + ra;
  let fy = (a * b * c).pow(2);
  let mut a = (fy % (a + b) + a) % (b + c) + 1;
  let mut b = (b % (b + c + a) + b) % (c + a) + 1;
  let mut c = (fy % (c + a) + c) % (a + b) + (a * b * c) % 3;

  let mut x = strings.chars().next().unwrap() as i32;
  let mut y = a * ((x + b).pow(2)) + c;
  println!("{}", y);
  output.push(y);

  for i in strings.chars().skip(1) {
    a = (y % b + a) % (b + a) + 1;
    b = (y % a + b) % c + 1;
    c = (x % (c * a) + c) % a + (a * b * c) % 11;
    y = (a * ((i as i32 + b).pow(2))) + c;
    x = i as i32;
    println!("{}", y);
    output.push(y);
  }
  println!("end!!");
}

fn twodecrypt() {
  let mut input = String::new();
  print!("a : ");
  io::stdout().flush().unwrap();
  io::stdin().read_line(&mut input).unwrap();
  let ra: i32 = input.trim().parse().unwrap();

  input.clear();
  print!("b : ");
  io::stdout().flush().unwrap();
  io::stdin().read_line(&mut input).unwrap();
  let rb: i32 = input.trim().parse().unwrap();

  input.clear();
  print!("c : ");
  io::stdout().flush().unwrap();
  io::stdin().read_line(&mut input).unwrap();
  let rc: i32 = input.trim().parse().unwrap();

  input.clear();
  print!("y : ");
  io::stdout().flush().unwrap();
  io::stdin().read_line(&mut input).unwrap();
  let ens: Vec<i32> = input
    .trim()
    .split(", ")
    .map(|s| s.parse().unwrap())
    .collect();

  let a = ra + rb;
  let b = rb + rc;
  let c = rc + ra;
  let fy = (a * b * c).pow(2);
  let mut a = (fy % (a + b) + a) % (b + c) + 1;
  let mut b = (b % (b + c + a) + b) % (c + a) + 1;
  let mut c = (fy % (c + a) + c) % (a + b) + (a * b * c) % 3;

  let mut x = 0;

  for &i in &ens {
    x = (((i - c) / a) as f64).sqrt() as i32 - b;
    a = (i % b + a) % (b + a) + 1;
    b = (i % a + b) % c + 1;
    c = (x % (c * a) + c) % a + (a * b * c) % 11;
    print!("{}", char::from(x as u8));
  }
  println!();
}

fn main() {
  twoencrypt();
  twodecrypt();
}

