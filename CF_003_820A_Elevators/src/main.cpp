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

    // long long result = 123456789012345678LL;
    // int a = 123456789;
    // result = (long long) a * a;

    string first_line;
    std::getline(std::cin, first_line);

    long long num_testcases = std::stoi(first_line);

    vector<int> result;

    for (long long i = 0; i < num_testcases; i++)
    {
        string test_line;
        std::getline(std::cin, test_line);

        int e1, e2s, e2d;
        sscanf_s(test_line.c_str(), "%d %d %d", &e1, &e2s, &e2d);

        int result_el(3);
        if ((e1 - 1) < (abs(e2s - e2d) + (e2d - 1)))
        {
            result_el = 1;
        }
        if ((e1 - 1) > (abs(e2s - e2d) + (e2d - 1)))
        {
            result_el = 2;
        }

        result.push_back(result_el);

    }

    for (auto& elem: result)
    {

        cout << elem << '\n';
    }


    return 0;
}
