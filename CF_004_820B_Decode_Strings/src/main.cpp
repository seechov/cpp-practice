// #include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const char* alphabet = "abcdefghijklmnopqrstuvwxyz";

char get_char(int index)
{
    if ((index > 26) || (index < 1))
    {
        return ' ';
    }
    else
    {
        return alphabet[index - 1];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string first_line;
    std::getline(std::cin, first_line);

    vector<string> result;

    long long num_testcases = std::stoi(first_line);

    for (long long i = 0; i < num_testcases; i++)
    {
        string length_line;
        std::getline(std::cin, length_line);

        long long line_length = std::stoi(length_line);

        string word_line;
        std::getline(std::cin, word_line);

        string decoded_line;

        for (long long i = line_length - 1; i >= 0; i--)
        {
            if ((word_line.at(i) == '0') && (i >= 2))
            {
                string for_decode;
                //= word_line.at(i-2) + word_line.at(i-1);
                for_decode.push_back(word_line.at(i-2));
                for_decode.push_back(word_line.at(i-1));
                int code = std::stoi(for_decode);
                char decoded_char = get_char(code);
                decoded_line.push_back(decoded_char);
                i -= 2;
            }
            else
            {
                string for_decode;
                for_decode.push_back(word_line.at(i));
                int code = std::stoi(for_decode);
                char decoded_char = get_char(code);
                decoded_line.push_back(decoded_char);
            }

        }

        reverse(decoded_line.begin(),decoded_line.end());

        result.push_back(decoded_line);

    }


    // char character = get_char(num_testcases);
    // string res_str(1, character);
    // cout << res_str << '\n';

    for (auto& elem: result)
    {

        cout << elem << '\n';
    }

    return 0;
}
