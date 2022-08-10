#include "stdc++.h"

using namespace std;

/// Given a positive integer , do the following:
///
/// If 1 <= n <= 9, print the lowercase English word corresponding to the number (e.g., one for , two for , etc.).
/// If n > 9, print Greater than 9.
/// Input Format
///
/// A single integer, n.
///
/// Constraints
///
/// 1 <= n <= 10^9
///
/// Output Format
///
/// If 1 <= n <= 9, then print the lowercase English word corresponding to the number (e.g., one for , two for , etc.); otherwise, print Greater than 9.
///
/// Sample Input 0
///
/// 5
/// Sample Output 0
///
/// five
/// Explanation 0
///
/// five is the English word for the number .
///
/// Sample Input 1
///
/// 8
/// Sample Output 1
///
/// eight
/// Explanation 1
///
/// eight is the English word for the number .
///
/// Sample Input 2
///
/// 44
/// Sample Output 2
///
/// Greater than 9
/// Explanation 2
///
/// n = 44 is greater than , so we print Greater than 9.

// trim from start (in place)
static inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
}


int main()
{
    string n_temp;
    getline(cin, n_temp);
    rtrim(n_temp);
    ltrim(n_temp);
    int n(std::stoi(n_temp));
    // std::from_chars(n_temp.data(), n_temp.data() + n_temp.size(), n);



    if (n == 1)
    {
        cout << "one";
    }
    else if (n == 2)
    {
        cout << "two";
    }
    else if (n == 3)
    {
        cout << "three";
    }
    else if (n == 4)
    {
        cout << "four";
    }
    else if (n == 5)
    {
        cout << "five";
    }
    else if (n == 6)
    {
        cout << "six";
    }
    else if (n == 7)
    {
        cout << "seven";
    }
    else if (n == 8)
    {
        cout << "eight";
    }
    else if (n == 9)
    {
        cout << "nine";
    }
    else
    {
        cout << "Greater than 9";
    }

    return 0;
}
