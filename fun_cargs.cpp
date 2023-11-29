#include <iostream>
using namespace std;

int add(int x, int y) { return x + y; }

int sub(int x, int y) { return x - y; }

int mul(int x, int y) { return x * y; }

int invoke(int x, int y, int (*func)(int, int)) { return func(x, y); }

int main()
{
    cout << invoke(20, 15, &add) << endl;
    cout << invoke(20, 15, &sub) << endl;
    cout << invoke(20, 15, &mul) << endl;
}