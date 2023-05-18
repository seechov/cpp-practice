// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    long long result = 123456789012345678LL;
    int a = 123456789;
    result = (long long) a * a;

    string first_line;
    string second_line;
    std::getline(std::cin, first_line);
    std::getline(std::cin, second_line);


    cout << result << '\n';

    return 0;
}
