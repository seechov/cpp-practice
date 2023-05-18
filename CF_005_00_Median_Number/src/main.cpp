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
    int num_of_testcases = std::stoi(first_line);

    std::vector<int> results;
    for (int i = 0; i < num_of_testcases; i++)
    {
        string input_line;
        std::getline(std::cin, input_line);

        int n1, n2, n3;
        std::sscanf(input_line.c_str(), "%d %d %d\n", &n1, &n2, &n3);
        if ((n1 < n2 && n1 > n3) || (n1 > n2 && n1 < n3))
        {
            results.push_back(n1);
        }
        else if ((n2 < n1 && n2 > n3) || (n2 > n1 && n2 < n3))
        {
            results.push_back(n2);
        }
        else
        {
            results.push_back(n3);
        }

    }

    for(int result : results)
    {
        cout << result << "\n";
    }

    return 0;
}
