// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int how_long_alphabet(std::string word)
{
    int biggest_offset = 0;
    for (int i = 0; i < word.size(); i++)
    {
        int offset = word[i] - 'a' + 1;
        if (offset > biggest_offset)
        {
            biggest_offset = offset;
        }
    }
    return biggest_offset;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string first_line;
    std::getline(std::cin, first_line);
    int num_of_testcases = std::stoi(first_line);

    std::vector<int> results;
    for (int i = 0; i < num_of_testcases; i++)
    {
        string input_line1;
        std::getline(std::cin, input_line1);
        string input_line2;
        std::getline(std::cin, input_line2);

        int string_length = std::stoi(input_line1);
        input_line2.resize(string_length);
        results.push_back(how_long_alphabet(input_line2));

    }

    for(int result : results)
    {
        cout << result << "\n";
    }

    return 0;
}
