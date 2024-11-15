package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"
)

func twoEncrypt() {
	var ra, rb, rc int
	fmt.Print("a : ")
	fmt.Scan(&ra)
	fmt.Print("b : ")
	fmt.Scan(&rb)
	fmt.Print("c : ")
	fmt.Scan(&rc)

	var inputString string
	fmt.Print("Input string: ")
	fmt.Scan(&inputString)

	output := []int{}
	a := ra + rb
	b := rb + rc
	c := rc + ra
	fy := math.Pow(float64(a*b*c), 2)
	a = int(math.Mod(fy, float64(a+b))+float64(a))%(b+c) + 1
	b = int(math.Mod(float64(b%(b+c+a))+float64(b), float64(c+a))) + 1
	c = int(math.Mod(fy, float64(c+a))+float64(c))%(a+b) + (a*b*c)%3

	x := int(inputString[0])
	y := a*int(math.Pow(float64(x+b), 2)) + c
	fmt.Println(y)
	output = append(output, y)

	for _, char := range inputString[1:] {
		a = (y%b + a)%(b+a) + 1
		b = (y%a + b)%c + 1
		c = (x%(c*a) + c)%a + (a*b*c)%11
		y = a*int(math.Pow(float64(int(char)+b), 2)) + c
		x = int(char)
		fmt.Println(y)
		output = append(output, y)
	}
	fmt.Println("end!!")
	fmt.Println("Output:", output)
}

func twoDecrypt() {
	var ra, rb, rc int
	fmt.Print("a : ")
	fmt.Scan(&ra)
	fmt.Print("b : ")
	fmt.Scan(&rb)
	fmt.Print("c : ")
	fmt.Scan(&rc)

	var ensInput string
	fmt.Print("y : ")
	fmt.Scan(&ensInput)

	ensStr := strings.Split(ensInput, ", ")
	ens := []int{}
	for _, s := range ensStr {
		num, err := strconv.Atoi(s)
		if err != nil {
			fmt.Println("Invalid input:", s)
			return
		}
		ens = append(ens, num)
	}

	des := []rune{}
	a := ra + rb
	b := rb + rc
	c := rc + ra
	fy := math.Pow(float64(a*b*c), 2)
	a = int(math.Mod(fy, float64(a+b))+float64(a))%(b+c) + 1
	b = int(math.Mod(float64(b%(b+c+a))+float64(b), float64(c+a))) + 1
	c = int(math.Mod(fy, float64(c+a))+float64(c))%(a+b) + (a*b*c)%3

	x := 0
	for _, i := range ens {
		iVal := float64(i)
		x = int(math.Sqrt((iVal-float64(c))/float64(a)) - float64(b))
		a = (i%b + a)%(b+a) + 1
		b = (i%a + b)%c + 1
		c = (x%(c*a) + c)%a + (a*b*c)%11

		fmt.Print(string(rune(x)))
		des = append(des, rune(x))
	}
	fmt.Println()
}

func main() {
	twoEncrypt()
	twoDecrypt()
}
