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

    long long n = std::stoi(first_line);
    int num_rows = 2 * n + 1;
    int num_columns = 2 * n + 1;
    vector<vector<int>> matrix(num_rows, vector<int>(num_columns));

    for(int i = 0; i < num_rows; i++)
    {
        matrix[i][i] = 0;
    }

    int filling_number = 1;
    for(int i = 0; i < num_rows; i++)
    {
        for(int j = (i + 1) % 2; j < num_columns; j += 2)
        {
            matrix[i][j] = filling_number;
            filling_number += 1;
        }
    }

    filling_number = -1;
    for(int j = 0; j < num_columns; j++)
    {
        for(int i = j % 2; i < num_rows; i += 2)
        {
            if (i != j)
            {
                matrix[i][j] = filling_number;
                filling_number -= 1;
            }
        }
    }

    for(int i = 0; i < num_rows; i++)
    {
        for(int j = 0; j < num_columns; j++)
        {
            if (j != num_columns - 1)
            {
                printf ("%d ", matrix[i][j]);
            }
            else
            {
                printf ("%d\n", matrix[i][j]);
            }
        }
    }

    return 0;
}
