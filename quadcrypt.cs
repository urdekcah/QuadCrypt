using System;
using System.Text;
using System.Linq;

class Program
{
  const int MAX_LENGTH = 1000;

  static void TwoEncrypt()
  {
    int ra, rb, rc, a, b, c, fy, x, y;
    StringBuilder output = new StringBuilder();

    Console.Write("a : ");
    ra = Convert.ToInt32(Console.ReadLine());

    Console.Write("b : ");
    rb = Convert.ToInt32(Console.ReadLine());

    Console.Write("c : ");
    rc = Convert.ToInt32(Console.ReadLine());

    Console.Write("Enter string: ");
    string? input = Console.ReadLine();
    if (input == null || input.Length > MAX_LENGTH)  // Проверка на null
    {
      Console.WriteLine("Input string is either null or exceeds maximum allowed length.");
      return;
    }

    a = ra + rb;
    b = rb + rc;
    c = rc + ra;
    fy = (int)Math.Pow(a * b * c, 2);

    a = (fy % (a + b) + a) % (b + c) + 1;
    b = (b % (b + c + a) + b) % (c + a) + 1;
    c = (fy % (c + a) + c) % (a + b) + (a * b * c) % 3;

    x = input[0];
    y = a * ((x + b) * (x + b)) + c;
    output.Append(y.ToString());

    for (int i = 1; i < input.Length; i++)
    {
      output.Append(", ");
      a = (y % b + a) % (b + a) + 1;
      b = (y % a + b) % c + 1;
      c = (x % (c * a) + c) % a + (a * b * c) % 11;

      x = input[i];
      y = a * ((x + b) * (x + b)) + c;
      output.Append(y.ToString());
    }

    Console.WriteLine("Encryption Output: " + output);
  }

  static void TwoDecrypt()
  {
    int ra, rb, rc, a, b, c, fy, x;
    long y;
    StringBuilder result = new StringBuilder();

    Console.Write("a : ");
    ra = Convert.ToInt32(Console.ReadLine());

    Console.Write("b : ");
    rb = Convert.ToInt32(Console.ReadLine());

    Console.Write("c : ");
    rc = Convert.ToInt32(Console.ReadLine());

    Console.Write("y (comma-separated): ");
    string? input = Console.ReadLine();
    if (input == null)  // Проверка на null
    {
      Console.WriteLine("Input is null.");
      return;
    }

    string[] tokens = input.Split(new[] { ", " }, StringSplitOptions.RemoveEmptyEntries);

    a = ra + rb;
    b = rb + rc;
    c = rc + ra;
    fy = (int)Math.Pow(a * b * c, 2);

    a = (fy % (a + b) + a) % (b + c) + 1;
    b = (b % (b + c + a) + b) % (c + a) + 1;
    c = (fy % (c + a) + c) % (a + b) + (a * b * c) % 3;

    foreach (var token in tokens)
    {
      if (!long.TryParse(token, out y))
      {
        Console.WriteLine("Invalid input format.");
        return;
      }

      // Приведение типов long к int для предотвращения ошибки CS0266
      x = (int)(Math.Sqrt((y - c) / a) - b);  
      a = (int)((y % b + a) % (b + a) + 1);  // Приведение к int
      b = (int)((y % a + b) % c + 1);    // Приведение к int
      c = (int)((x % (c * a) + c) % a + (a * b * c) % 11);  // Приведение к int

      result.Append((char)x);
    }

    Console.WriteLine("Decryption Result: " + result);
  }

  static void Main()
  {
    try
    {
      Console.Write("1. Encrypt\n2. Decrypt\nEnter your choice: ");
      int choice = Convert.ToInt32(Console.ReadLine());

      if (choice == 1)
      {
        TwoEncrypt();
      }
      else if (choice == 2)
      {
        TwoDecrypt();
      }
      else
      {
        Console.WriteLine("Invalid choice");
      }
    }
    catch (Exception ex)
    {
      Console.WriteLine("An error occurred: " + ex.Message);
    }
  }
}
