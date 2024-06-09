#include <iostream>
#include <chrono>
#include <math.h>
using namespace std;


bool divisibility_check(int n)
{
    if (n == 0 || n == 1)
        return false; // false if n equals 0 or 1

    for (int i = 2; i < n; i++) { // looking for 2nd divider since 1st is always 1
        if (n % i == 0)
            return false; // number is not prime if it's divisible by i
    }
    return true; // otherwise number is prime
}

bool divisibility_check_using_square_root(int n)
{
    if (n == 0 || n == 1)
        return false; // false if n equals 0 or 1

    for (int i = 2; i <= sqrt(n); i++) { // looking for 2nd divider since 1st is always 1
        if (n % i == 0)
            return false; // number is not prime if it's divisible by i
    }
    return true; // otherwise number is prime
}

void eratosthenes_sieve(int n)
{
    bool* testArray = new bool[n + 1];
    for (int i = 2; i <= n; i++)
        testArray[i] = true; // set all elements inside array to true

    for (int i = 2; i < n; i++) {
        for (int x = i + i; x <= n; x += i)
            testArray[x] = false; //set multiplies inside array to false
    }

    for (int i = 2; i <= n; i++) {
        if (testArray[i])
            cout << i << ", ";
    }
}

void linear_sieve(int n)
{
    bool* testArray = new bool[n + 1];
    for (int i = 2; i <= n; i++)
        testArray[i] = true; // set all elements inside array to true

    for (int i = 2; i < n; i++) {
        if (testArray[i]) { // this will avoid going through numbers that were already removed
            for (int x = i * i; x <= n; x += i) // set powers of elements inside array to false
                testArray[x] = false;
        }
    }

    for (int i = 2; i <= n; i++) {
        if (testArray[i])
            cout << i << ", ";
    }
}

int main()
{
    int a = 0;
    cout << "Max range to find prime numbers in: ";
    cin >> a;

    // start divisibility check section
    cout << "1. Divisibility check" << endl;
    auto timerStart1 = chrono::high_resolution_clock::now(); // start of chrono for divisibility check

    for (int i = 2; i <= a; i++) {
        if (divisibility_check(i))
            cout << i << ", ";
    }

    auto timerStop1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeElapsed1 = timerStop1 - timerStart1; // time elapsed since chrono started.
    auto sec1 = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed1); // seconds
    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed1 - sec1); // milliseconds

    cout << "\n\nTime: " << sec1.count() << " seconds and " << ms1.count() << " milliseconds" << endl; // end of chrono for divisibility check
    cout << "---------------------------------------------" << endl; // end of divisibility check



    // start divisibility check using square root section
    cout << "\n2. Divisibility check using square root" << endl;
    auto timerStart2 = chrono::high_resolution_clock::now(); // start of chrono for divisibility check using square root

    for (int i = 2; i <= a; i++) {
        if (divisibility_check_using_square_root(i))
            cout << i << ", ";
    }

    auto timerStop2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeElapsed2 = timerStop2 - timerStart2; // time elapsed since chrono started.
    auto sec2 = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed2); // seconds
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed2 - sec2); // milliseconds

    cout << "\n\nTime: " << sec2.count() << " seconds and " << ms2.count() << " milliseconds" << endl; // end of chrono for divisibility check using square root
    cout << "---------------------------------------------"; // end of divisibility check using square root



    // start eratosthenes sieve
    cout << "\n\n3. Eratosthenes sieve" << endl;
    auto timerStart3 = chrono::high_resolution_clock::now(); // start of chrono for eratosthenes sieve

    eratosthenes_sieve(a);

    auto timerStop3 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeElapsed3 = timerStop3 - timerStart3; // time elapsed since chrono started.
    auto sec3 = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed3); // seconds
    auto ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed3 - sec3); // milliseconds

    cout << "\n\nTime: " << sec3.count() << " seconds and " << ms3.count() << " milliseconds" << endl; // end of chrono for eratosthenes sieve
    cout << "---------------------------------------------"; // end of chrono for eratosthenes sieve



    // start linear sieve
    cout << "\n\n4. Linear sieve" << endl;
    auto timerStart4 = chrono::high_resolution_clock::now(); // start of chrono for linear sieve

    linear_sieve(a);

    auto timerStop4 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timeElapsed4 = timerStop4 - timerStart4; // time elapsed since chrono started.
    auto sec4 = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed4); // seconds
    auto ms4 = std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed4 - sec4); // milliseconds

    cout << "\n\nTime: " << sec4.count() << " seconds and " << ms4.count() << " milliseconds" << endl; // end of chrono for linear sieve
    cout << "---------------------------------------------"; // end of chrono for linear sieve
}