#include <bits/stdc++.h>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

/*
 * Complete the 'sockMerchant' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER_ARRAY ar
 */


string build_with_consecutive_letters_limit(int countX, int countY) {
    string result;
    const int consecutive_count_limit = 3;
    int consecutive_x = 0;
    int consecutive_y = 0;
    while ((countX > 0) || (countY > 0)) {
        if (countX > countY) {
            if (consecutive_x < consecutive_count_limit) {
                result.append("X");
                countX -= 1;
                consecutive_x += 1;
                consecutive_y = 0;
            } else if (countY > 0) {
                result.append("Y");
                countY -= 1;
                consecutive_x = 0;
                consecutive_y += 1;
            }
        } else {
            if (consecutive_y < consecutive_count_limit) {
                result.append("Y");
                countY -= 1;
                consecutive_x = 0;
                consecutive_y += 1;
            } else if (countX > 0) {
                result.append("X");
                countX -= 1;
                consecutive_x += 1;
                consecutive_y = 0;
            }
        }

    }
    return result;
}

//        while (consecutive_x < consecutive_count_limit && consecutive_y < consecutive_count_limit) {
//            if (countX > countY) {
//                consecutive_x += 1;
//                if (consecutive_x >= consecutive_count_limit) {
//                    continue;
//                }
//                countX -= 1;
//                result.append("X");
//            } else {
//                consecutive_y += 1;
//                if (consecutive_y >= consecutive_count_limit) {
//                    continue;
//                }
//                countY -= 1;
//                result.append("Y");
//            }
//        }

int main() {
//    string n_temp;
//    getline(cin, n_temp);
//    int n = stoi(ltrim(rtrim(n_temp)));

    //const int input_array_size(2);
    string ar_temp_temp;
    getline(cin, ar_temp_temp);
    vector<string> ar_temp = split(rtrim(ar_temp_temp));
    vector<int> ar(ar_temp.size());
    for (int i = 0; i < ar_temp.size(); i++) {
        int ar_item = stoi(ar_temp[i]);
        ar[i] = ar_item;
    }


    std::cout << build_with_consecutive_letters_limit(ar.at(0), ar.at(1)) << "\n";
    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string& str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
