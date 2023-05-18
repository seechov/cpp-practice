// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <cstdint>
#include <algorithm>
#include <cstdio>
using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string first_line;
    string second_line;
    std::getline(std::cin, first_line);
    std::getline(std::cin, second_line);

    int32_t w = std::stoi(first_line);

    int32_t n, k;
    std::sscanf(second_line.c_str(), "%d %d\n", &n, &k);


    list <int32_t> image_heights;
    for (int32_t i = 0; i < n; i++)
    {
        string input_line;
        std::getline(std::cin, input_line);

        int32_t h_prime, w_prime;
        std::sscanf(input_line.c_str(), "%dx%d\n", &w_prime, &h_prime);

        int32_t h;
        if (w_prime != 0)
        {
            h = static_cast<int32_t>(std::ceil(static_cast<double>(h_prime) * static_cast<double>(w) / static_cast<double>(w_prime)));
        }
        else
        {
            h = 0;
        }

        image_heights.push_back(h);
    }

    image_heights.sort();

    int64_t min_height = 0;
    int32_t counter = 0;
    for (auto iterator = image_heights.begin(); iterator != image_heights.end() && counter < k; ++iterator, ++counter)
    {
        min_height += *iterator;
    }

    int64_t max_height = 0;
    counter = 0;
    for (auto iterator = image_heights.end(); iterator != image_heights.begin() && counter < k; ++counter)
    {
        --iterator;
        max_height += *iterator;
    }

    printf ("%ld\n", min_height);
    printf ("%ld\n", max_height);
    // cout << result << '\n';

    return 0;
}
