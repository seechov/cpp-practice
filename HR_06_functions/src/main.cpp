#include <iostream>
#include <cstdio>
using namespace std;

int max_of_four(int a, int b, int c, int d)
{
    int max_pair1 = a > b ? a : b;
    int max_pair2 = c > d ? c : d;

    return max_pair1 > max_pair2 ? max_pair1 : max_pair2;
}

int main()
{
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);

    return 0;
}
