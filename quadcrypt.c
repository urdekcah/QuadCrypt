#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 1000

void twoencrypt() {
  int ra, rb, rc, a, b, c, fy, x, y;
  char strings[MAX_LENGTH];
  long long output[MAX_LENGTH];
  int output_index = 0;

  printf("a : ");
  scanf("%d", &ra);
  printf("b : ");
  scanf("%d", &rb);
  printf("c : ");
  scanf("%d", &rc);
  printf("Enter string: ");
  scanf(" %[^\n]", strings);

  a = ra + rb;
  b = rb + rc;
  c = rc + ra;
  fy = (long long)(a * b * c) * (a * b * c);
  a = (fy % (a + b) + a) % (b + c) + 1;
  b = (b % (b + c + a) + b) % (c + a) + 1;
  c = (fy % (c + a) + c) % (a + b) + (a * b * c) % 3;

  x = (int)strings[0];
  y = a * ((x + b) * (x + b)) + c;
  printf("%d\n", y);
  output[output_index++] = y;

  for (int i = 1; i < strlen(strings); i++) {
    a = (y % b + a) % (b + a) + 1;
    b = (y % a + b) % c + 1;
    c = (x % (c * a) + c) % a + (a * b * c) % 11;
    x = (int)strings[i];
    y = a * ((x + b) * (x + b)) + c;
    printf("%d\n", y);
    output[output_index++] = y;
  }

  printf("end!!\n");
}

void twodecrypt() {
  int ra, rb, rc, a, b, c, fy, x;
  long long y;
  char des[MAX_LENGTH];
  int des_index = 0;
  char input[MAX_LENGTH];

  printf("a : ");
  scanf("%d", &ra);
  printf("b : ");
  scanf("%d", &rb);
  printf("c : ");
  scanf("%d", &rc);
  printf("y : ");
  scanf(" %[^\n]", input);

  a = ra + rb;
  b = rb + rc;
  c = rc + ra;
  fy = (long long)(a * b * c) * (a * b * c);
  a = (fy % (a + b) + a) % (b + c) + 1;
  b = (b % (b + c + a) + b) % (c + a) + 1;
  c = (fy % (c + a) + c) % (a + b) + (a * b * c) % 3;

  char *token = strtok(input, ", ");
  while (token != NULL) {
    y = atoll(token);
    x = (int)(sqrt((y - c) / a) - b);
    a = (y % b + a) % (b + a) + 1;
    b = (y % a + b) % c + 1;
    c = (x % (c * a) + c) % a + (a * b * c) % 11;
    printf("%c", (char)x);
    des[des_index++] = (char)x;
    token = strtok(NULL, ", ");
  }
  des[des_index] = '\0';
  printf("\n");
}

int main() {
  int choice;
  printf("1. Encrypt\n2. Decrypt\nEnter your choice: ");
  scanf("%d", &choice);

  if (choice == 1) {
    twoencrypt();
  } else if (choice == 2) {
    twodecrypt();
  } else {
    printf("Invalid choice\n");
  }

  return 0;
}