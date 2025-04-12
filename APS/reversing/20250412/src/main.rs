use base64::{decode};
use std::io::{self, Write};

fn main() {
    print!("input: ");
    io::stdout().flush().unwrap();
    let mut input:String = String::new();
    std::io::stdin().read_line(&mut input).expect("input error");
    let input = input.trim();
    if !check(&input.to_string()) {
        println!("Wrong!");
    }else {
        println!("{}", "Correct!");

        let var1 = "x^_nzQr~@tu`}^qr@Ar~MNulx*u(PH$$";
        let mut flag = String::new();
        let mut x = 0;
        for i in 0..10{
            x^=input.as_bytes()[i];
        }
        for i in var1.chars() {
            flag.push(((i as u8 ^ x as u8)as u8) as char);
        }
        match decode(&flag) {
            Ok(decoded) => {
                match String::from_utf8(decoded) {
                    Ok(decoded_str) => {
                        println!("flag: {}", decoded_str);
                    }
                    Err(e) => {
                        println!("Error converting to string: {}", e);
                    }
                }
            }
            Err(e) => {
                println!("Error decoding: {}", e);
            }
        }
        println!("done");
    }
}
fn check(_s:&String) -> bool {
    let mut i:i32 = 0;
    let mut data1:[u8;10] = [ 0x66, 0x5c, 0x50, 0x3d, 0x50, 0x4a, 0x75, 0x3f, 0x2e, 0x30 ];
    let mut secret:String = String::new();
    while i < 10 {
        secret.push((data1[i as usize]^0x0F) as char);
        data1[i as usize] ^= 0x0F;
        i += 1;
    }
    if _s.cmp(&secret) != std::cmp::Ordering::Equal {
        return false;
    }
    return true;
}