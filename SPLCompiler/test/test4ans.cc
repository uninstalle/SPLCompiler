#include <iostream>

int f;
int k;
int go(int &b, int a)
{
    int fk;
    double t;
    int retval;
    if (a > 0)
    {
        retval = a * go(b, a - 1);
    }
    else
    {
        retval = 1;
    }
    b = b + retval;
    k = k + retval;
    return retval;
}

int main()
{
    k = 0;
    f = go(k, 5);
    std::cout << f << std::endl;
    std::cout << k << std::endl;
}
