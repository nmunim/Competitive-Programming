// C++ program to find multiplicative modulo inverse using
// Extended Euclid algorithm.
#include <bits/stdc++.h>

using namespace std;

// C function for extended Euclidean Algorithm
LL gcdExtended(LL a, LL b, LL *x, LL *y);

// Function to find modulo inverse of a
LL modInverse(LL a, LL m)
{
    LL x, y;
    LL g = gcdExtended(a, m, &x, &y);
    if (g != 1) return 0;
    // m is added to handle negative x
    LL res = (x%m + m) % m;
    return res;
}

// C function for extended Euclidean Algorithm
LL gcdExtended(LL a, LL b, LL *x, LL *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    LL x1, y1; // To store results of recursive call
    LL gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

// Driver Program
int main()
{
    LL a, m;
    while (1)
    {
        cin >> a >> m;
        cout << modInverse(a, m) << endl;
    }
    return 0;
}
