def twoencrypt ():
  ra = int(input('a : '))
  rb=int(input('b : '))
  rc =int(input('c : '))
  strings = input('')
  output = []
  a = ra+rb
  b = rb+rc
  c = rc+ra
  fy = ((a*b*c)**2)
  a = (fy%(a+b)+a)%(b+c)+1
  b = (b%(b+c+a)+b)%(c+a)+1
  c = (fy%(c+a)+c)%(a+b)+(a*b*c)%3
  re = 0
  x = int(ord(strings[0]))
  y = a*((x+b)**2)+c
  print(y)
  output.append(y)
  for i in strings[1:]:
    a = (y%b+a)%(b+a)+1
    b = (y%a+b)%c+1
    c = (x%(c*a)+c)%a+(a*b*c)%11
    y = (a*((int(ord(i))+b)**2))+c
    x = int(ord(i))
    print(y)
    output.append(y)
  print('end!!')

def twodecrypt():
  ra = int(input('a : '))
  rb=int(input('b : '))
  rc =int(input('c : '))
  ens = input('y : ').split(', ')
  des = []
  a = ra+rb
  b = rb+rc
  c = rc+ra
  fy = ((a*b*c)**2)
  a = (fy%(a+b)+a)%(b+c)+1
  b = (b%(b+c+a)+b)%(c+a)+1
  c = (fy%(c+a)+c)%(a+b)+(a*b*c)%3
  x = 0
  for i in ens:
    i = int(i)
    x = int((((i-c)/a)**0.5)-b)
    a = (i%b+a)%(b+a)+1
    b = (i%a+b)%c+1
    c = (x%(c*a)+c)%a+(a*b*c)%11
    print(chr(x),end='')
    des.append(chr(x))
  print()
  
def main():
  twoencrypt()
  twodecrypt()

if __name__ == '__main__':
  main()