#include <iostream>
#include <cstring>
#include <cmath>
#include <string>

#define MAX_LENGTH 1000

void twoencrypt() {
  int ra, rb, rc, a, b, c, fy, x, y;
  char strings[MAX_LENGTH];
  long long output[MAX_LENGTH];
  int output_index = 0;

  std::cout << "a : ";
  std::cin >> ra;
  std::cout << "b : ";
  std::cin >> rb;
  std::cout << "c : ";
  std::cin >> rc;
  std::cout << "Enter string: ";
  std::cin.ignore();
  std::cin.getline(strings, MAX_LENGTH);

  a = ra + rb;
  b = rb + rc;
  c = rc + ra;
  fy = static_cast<long long>(a * b * c) * (a * b * c);
  a = (fy % (a + b) + a) % (b + c) + 1;
  b = (b % (b + c + a) + b) % (c + a) + 1;
  c = (fy % (c + a) + c) % (a + b) + (a * b * c) % 3;

  x = static_cast<int>(strings[0]);
  y = a * ((x + b) * (x + b)) + c;
  std::cout << y << std::endl;
  output[output_index++] = y;

  for (int i = 1; i < std::strlen(strings); i++) {
    a = (y % b + a) % (b + a) + 1;
    b = (y % a + b) % c + 1;
    c = (x % (c * a) + c) % a + (a * b * c) % 11;
    x = static_cast<int>(strings[i]);
    y = a * ((x + b) * (x + b)) + c;
    std::cout << y << std::endl;
    output[output_index++] = y;
  }

  std::cout << "end!!" << std::endl;
}

void twodecrypt() {
  int ra, rb, rc, a, b, c, fy, x;
  long long y;
  char des[MAX_LENGTH];
  int des_index = 0;
  char input[MAX_LENGTH];

  std::cout << "a : ";
  std::cin >> ra;
  std::cout << "b : ";
  std::cin >> rb;
  std::cout << "c : ";
  std::cin >> rc;
  std::cout << "y : ";
  std::cin.ignore();
  std::cin.getline(input, MAX_LENGTH);

  a = ra + rb;
  b = rb + rc;
  c = rc + ra;
  fy = static_cast<long long>(a * b * c) * (a * b * c);
  a = (fy % (a + b) + a) % (b + c) + 1;
  b = (b % (b + c + a) + b) % (c + a) + 1;
  c = (fy % (c + a) + c) % (a + b) + (a * b * c) % 3;

  char *token = std::strtok(input, ", ");
  while (token != NULL) {
    y = std::stoll(token);
    x = static_cast<int>(std::sqrt((y - c) / a) - b);
    a = (y % b + a) % (b + a) + 1;
    b = (y % a + b) % c + 1;
    c = (x % (c * a) + c) % a + (a * b * c) % 11;
    std::cout << static_cast<char>(x);
    des[des_index++] = static_cast<char>(x);
    token = std::strtok(NULL, ", ");
  }
  des[des_index] = '\0';
  std::cout << std::endl;
}

int main() {
  int choice;
  std::cout << "1. Encrypt\n2. Decrypt\nEnter your choice: ";
  std::cin >> choice;

  if (choice == 1) {
    twoencrypt();
  } else if (choice == 2) {
    twodecrypt();
  } else {
    std::cout << "Invalid choice" << std::endl;
  }

  return 0;
}
