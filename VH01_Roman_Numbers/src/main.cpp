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

std::string numerals(int num) {
    std::string roman_numerals;
    switch((num / 1000) % 10) {
    case 1: {roman_numerals += "M"; break;};
    case 2: {roman_numerals += "MM"; break;};
    case 3: {roman_numerals += "MMM"; break;};
    }
    switch((num / 100) % 10) {
    case 1: {roman_numerals += "C"; break;};
    case 2: {roman_numerals += "CC"; break;};
    case 3: {roman_numerals += "CCC"; break;};
    case 4: {roman_numerals += "CD"; break;};
    case 5: {roman_numerals += "D"; break;};
    case 6: {roman_numerals += "DC"; break;};
    case 7: {roman_numerals += "DCC"; break;};
    case 8: {roman_numerals += "DCCC"; break;};
    case 9: {roman_numerals += "CM"; break;};
    }
    switch((num / 10) % 10) {
    case 1: {roman_numerals += "X"; break;};
    case 2: {roman_numerals += "XX"; break;};
    case 3: {roman_numerals += "XXX"; break;};
    case 4: {roman_numerals += "XL"; break;};
    case 5: {roman_numerals += "L"; break;};
    case 6: {roman_numerals += "LX"; break;};
    case 7: {roman_numerals += "LXX"; break;};
    case 8: {roman_numerals += "LXXX"; break;};
    case 9: {roman_numerals += "XC"; break;};
    }
    switch(num % 10) {
    case 1: {roman_numerals += "I"; break;};
    case 2: {roman_numerals += "II"; break;};
    case 3: {roman_numerals += "III"; break;};
    case 4: {roman_numerals += "IV"; break;};
    case 5: {roman_numerals += "V"; break;};
    case 6: {roman_numerals += "VI"; break;};
    case 7: {roman_numerals += "VII"; break;};
    case 8: {roman_numerals += "VIII"; break;};
    case 9: {roman_numerals += "IX"; break;};
    }

    return roman_numerals;
}

int main() {
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

//    string ar_temp_temp;
//    getline(cin, ar_temp_temp);
//    vector<string> ar_temp = split(rtrim(ar_temp_temp));
//    vector<int> ar(n);
//    for (int i = 0; i < n; i++) {
//        int ar_item = stoi(ar_temp[i]);
//        ar[i] = ar_item;
//    }

    std::string result = numerals(n);
    std::cout << result << "\n";
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
