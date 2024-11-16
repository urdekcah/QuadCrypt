import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
  public static void TwoEncrypt() {
    Scanner scanner = new Scanner(System.in);

    System.out.print("a: ");
    int ra = scanner.nextInt();
    System.out.print("b: ");
    int rb = scanner.nextInt();
    System.out.print("c: ");
    int rc = scanner.nextInt();

    System.out.print("Input string: ");
    scanner.nextLine();
    String strings = scanner.nextLine();

    List<Integer> output = new ArrayList<>();
    int a = ra + rb;
    int b = rb + rc;
    int c = rc + ra;
    long fy = (long) Math.pow(a * b * c, 2);

    a = (int) ((fy % (a + b) + a) % (b + c)) + 1;
    b = (int) ((b % (b + c + a) + b) % (c + a)) + 1;
    c = (int) ((fy % (c + a) + c) % (a + b)) + (a * b * c) % 3;

    int re = 0;
    int x = (int) strings.charAt(0);
    int y = a * (int) Math.pow((x + b), 2) + c;

    System.out.println(y);
    output.add(y);

    for (int i = 1; i < strings.length(); i++) {
      a = (int) ((y % b + a) % (b + a)) + 1;
      b = (int) ((y % a + b) % c) + 1;
      c = (int) ((x % (c * a) + c) % a) + (a * b * c) % 11;

      y = a * (int) Math.pow((strings.charAt(i) + b), 2) + c;
      x = (int) strings.charAt(i);

      System.out.println(y);
      output.add(y);
    }

    System.out.println("end!!");
  }

  public static void TwoDecrypt() {
    Scanner scanner = new Scanner(System.in);

    System.out.print("a: ");
    int ra = scanner.nextInt();
    System.out.print("b: ");
    int rb = scanner.nextInt();
    System.out.print("c: ");
    int rc = scanner.nextInt();

    System.out.print("y (comma-separated): ");
    scanner.nextLine();
    String[] encryptedValues = scanner.nextLine().split(", ");
    List<Character> des = new ArrayList<>();

    int a = ra + rb;
    int b = rb + rc;
    int c = rc + ra;
    long fy = (long) Math.pow(a * b * c, 2);

    a = (int) ((fy % (a + b) + a) % (b + c)) + 1;
    b = (int) ((b % (b + c + a) + b) % (c + a)) + 1;
    c = (int) ((fy % (c + a) + c) % (a + b)) + (a * b * c) % 3;

    int x = 0;

    for (String str : encryptedValues) {
      int i = Integer.parseInt(str);
      x = (int) (Math.sqrt((i - c) / (double) a) - b);

      a = (int) ((i % b + a) % (b + a)) + 1;
      b = (int) ((i % a + b) % c) + 1;
      c = (int) ((x % (c * a) + c) % a) + (a * b * c) % 11;

      System.out.print((char) x);
      des.add((char) x);
    }

    System.out.println();
  }

  public static void Main(String[] args) {
    TwoEncrypt();
    TwoDecrypt();
  }
}
