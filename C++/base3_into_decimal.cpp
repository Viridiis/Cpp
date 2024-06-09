#include <cstdio>
#include <iostream>
#include <math.h>
using namespace std;

int ternaryIntoDecimal(int a)
{
    if (a != 0) {

        int number = 0, i = 0, remainder;

        while (a != 0) {
            remainder = a % 10;
            a /= 10;

            number += remainder * pow(3, i);
            ++i;
        }
        return number;
    }
    else
        return 0;
}

void decimalIntoTernary(int a)
{
    if (a == 0)
        return;

    int x = a % 3;
    a /= 3;
    if (x < 0)
        a += 1;

    decimalIntoTernary(a);

    if (x < 0)
        cout << x + (3 * -1);
    else
        cout << x;
}

void result(int a)
{
    if (a != 0) {
        decimalIntoTernary(a);
    }
    else
        cout << "0" << endl;
}

int digit(int a)
{
    if (a == 0)
        return 1;
    int count = 0;
    while (a != 0) {
        a = a / 10;
        count++;
    }
    return count;
}

struct Pair
{
    int number1;
    int number2;
};


// Driver code
int main()
{
    int pairNumber = 2;
    
    Pair* addition = new Pair[pairNumber];

    cout << "Insert numbers: " << endl;
    for (int i = 0; i < pairNumber; i++)
    {
        cin >> addition[i].number1 >> addition[i].number2;
        if (digit(addition[i].number1) > 9 || digit(addition[i].number2) > 9)
        {
            cout << "Too long number " << endl;
            exit(EXIT_SUCCESS);
        }
    }

    cout << endl << "Results" << endl;
    cout << "=========================" << endl << endl;

    for (int i = 0; i < pairNumber; i++)
    {
        int a = ternaryIntoDecimal(addition[i].number1);
        int b = ternaryIntoDecimal(addition[i].number2);
        int sum = a + b;
        result(sum);
        cout << endl;
    }
}