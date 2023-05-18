// Copyright 2023 Aleksei Sychev
// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    uint64_t result = 123456789012345678LL;
    int a = 123456789;
    result = (uint64_t) a * a;

    std::string first_line;
    std::string second_line;
    std::string hello;
    std::getline(std::cin, first_line);
    std::getline(std::cin, second_line);

    std::cout << result << '\n';

    return 0;
}
