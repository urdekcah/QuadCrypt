#!/bin/bash

function TwoEncrypt() {
  local output=()

  read -p "a : " ra
  read -p "b : " rb
  read -p "c : " rc
  read -p "Input string: " strings

  a=$(( ra + rb ))
  b=$(( rb + rc ))
  c=$(( rc + ra ))
  fy=$(( a * b * c * (a * b * c) ))

  a=$(( (fy % (a + b) + a) % (b + c) + 1 ))
  b=$(( (b % (b + c + a) + b) % (c + a) + 1 ))
  c=$(( (fy % (c + a) + c) % (a + b) + (a * b * c) % 3 ))

  x=$(printf "%d" "'${strings:0:1}")
  y=$(( a * (x + b) * (x + b) + c ))
  output+=($y)

  for ((i=1; i<${#strings}; i++)); do
    [ $b -eq 0 ] && b=1
    [ $a -eq 0 ] && a=1
    [ $c -eq 0 ] && c=1

    a=$(( (y % b + a) % (b + a) + 1 ))
    b=$(( (y % a + b) % c + 1 ))
    c=$(( (x % (c * a) + c) % a + (a * b * c) % 11 ))

    x=$(printf "%d" "'${strings:$i:1}")
    y=$(( a * (x + b) * (x + b) + c ))
    output+=($y)
  done

  echo "${output[@]}"
}

function TwoDecrypt() {
  read -p "a : " ra
  read -p "b : " rb
  read -p "c : " rc
  read -p "y : " inputStr

  IFS=', ' read -r -a ens <<< "$inputStr"

  a=$(( ra + rb ))
  b=$(( rb + rc ))
  c=$(( rc + ra ))
  fy=$(( a * b * c * (a * b * c) ))

  a=$(( (fy % (a + b) + a) % (b + c) + 1 ))
  b=$(( (b % (b + c + a) + b) % (c + a) + 1 ))
  c=$(( (fy % (c + a) + c) % (a + b) + (a * b * c) % 3 ))

  for i in "${ens[@]}"; do
    [ $b -eq 0 ] && b=1
    [ $a -eq 0 ] && a=1
    [ $c -eq 0 ] && c=1

    temp=$(( i - c ))
    x=1
    while ((x * x * a <= temp)); do
      ((x++))
    done
    ((x--))
    x=$(( x - b ))

    printf "\\$(printf '%03o' "$x")"

    a=$(( (i % b + a) % (b + a) + 1 ))
    b=$(( (i % a + b) % c + 1 ))
    c=$(( (x % (c * a) + c) % a + (a * b * c) % 11 ))
  done
  echo
}

encrypted=$(TwoEncrypt)
echo "$encrypted"
TwoDecrypt
