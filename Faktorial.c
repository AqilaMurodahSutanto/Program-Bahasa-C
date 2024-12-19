#include <stdio.h>

int HitungFaktorial(int input)
{
    if (input > 1)
    {
        return input * HitungFaktorial(input - 1);
    }
    else
    {
        return 1;
    }
}

int main(void)
{
    int a = 5;
    printf("%d = %d\n ", a, HitungFaktorial(a));

    return 0;
}

// #include <stdio.h>

// int hitungFibonacci(int n) {
//   if (n <= 1)
//     return n;
//   else
//     return hitungFibonacci(n - 1) + hitungFibonacci(n - 2);
// }

// int main(void) {
//   printf("## Program Bahasa C Menghitung Bilangan Fibonacci ## \n");
//   printf("=================================================== \n\n");

//   int angka;

//   printf("Input angka: ");
//   scanf("%d", &angka);

//   printf("Fibonacci dari %d adalah %d \n", angka, hitungFibonacci(angka));

//   return 0;
// }