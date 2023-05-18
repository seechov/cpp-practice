#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    string first_line;
    string second_line;
    std::getline(std::cin, first_line);
    std::getline(std::cin, second_line);

    std::transform(first_line.begin(), first_line.end(), first_line.begin(),
                   [](unsigned char c)
    {
        return std::tolower(c);
    });
    std::transform(second_line.begin(), second_line.end(), second_line.begin(),
                   [](unsigned char c)
    {
        return std::tolower(c);
    });

    int result(0);
    for (int i = 0; (i < first_line.size()) && (i < second_line.size()); i++)
    {
        if (first_line.at(i) < second_line.at(i))
        {
            result = -1;
            break;
        }
        if (first_line.at(i) > second_line.at(i))
        {
            result = 1;
            break;
        }
    }

    cout << result << endl;

    return 0;
}
