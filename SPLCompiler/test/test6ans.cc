#include <iostream>

int ans;

int gcd(int a, int b)
{
    int retval;
    if (b == 0)
    {
        retval = a;
    }
    else
    {
        retval = gcd(b, a % b);
    }
    return retval;
}

int main()
{
    ans = gcd(9, 36) * gcd(3, 6);
    std::cout << ans << std::endl;
}