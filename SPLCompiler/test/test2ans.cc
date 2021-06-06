#include <iostream>

int i;

int go(int a)
{
    int retval;
    if (a == 1)
    {
        retval = 1;
    }
    else
    {
        if (a == 2)
        {
            retval = 1;
        }
        else
        {
            retval = go(a - 1) + go(a - 2);
        }
    }
    return retval;
}

int main()
{
    i = go(10);
    std::cout << i << std::endl;
}
