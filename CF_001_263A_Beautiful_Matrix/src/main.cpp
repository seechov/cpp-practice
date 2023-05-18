#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
    string s;
    int num_of_moves(0);
    for (int i = 0; i < 5; i++)
    {
        // cin >> s;
        int m0, m1, m2, m3, m4;
        int one_pos(-1);
        scanf_s("%d %d %d %d %d", &m0, &m1, &m2, &m3, &m4);
        if (m0 == 1)
        {
            one_pos = 0;
        }
        if (m1 == 1)
        {
            one_pos = 1;
        }
        if (m2 == 1)
        {
            one_pos = 2;
        }
        if (m3 == 1)
        {
            one_pos = 3;
        }
        if (m4 == 1)
        {
            one_pos = 4;
        }
        if (one_pos >= 0)
        {
            num_of_moves = abs(2 - one_pos) + abs(2 - i);
        }
    }

    cout << num_of_moves << endl;

    return 0;
}


// int main()
// {
//     string first_line;
//     string second_line;
//     std::getline(std::cin, first_line);
//     std::getline(std::cin, second_line);
//
//     std::transform(first_line.begin(), first_line.end(), first_line.begin(),
//                    [](unsigned char c)
//     {
//         return std::tolower(c);
//     });
//     std::transform(second_line.begin(), second_line.end(), second_line.begin(),
//                    [](unsigned char c)
//     {
//         return std::tolower(c);
//     });
//
//     int result(0);
//     for (int i = 0; (i < first_line.size()) && (i < second_line.size()); i++)
//     {
//         if (first_line.at(i) < second_line.at(i))
//         {
//             result = -1;
//             break;
//         }
//         if (first_line.at(i) > second_line.at(i))
//         {
//             result = 1;
//             break;
//         }
//     }
//
//     cout << result << endl;
//
//     return 0;
// }
