#include <string>
#include <iostream>
using namespace std;

bool IsKPeriodic(string str, int k) {
    if (str.length() % k != 0) //If the length of the string is not a multiple of k, then there is nothing to talk about
        return 0;
    string substr = str.substr(0, k); //finding the first substring
    for (int i = 0; i < str.length() / k; ++i) {
        if (str.substr(i * k, k) != substr) //check that all subsequent substrings match the first one
            return 0; //If not matched, the string is not short K
    }
    return 1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    //A number of tests have been performed
    cout << IsKPeriodic("abcabcabcabc", 3) << '\n';
    cout << IsKPeriodic("abcabcabcabc", 2) << '\n';
    cout << IsKPeriodic("abcdabcdabcdabcd", 4) << '\n';
    cout << IsKPeriodic("aaa", 3) << '\n';
    cout << IsKPeriodic("ababababab", 5) << '\n';
    cout << IsKPeriodic("ababababab", 2) << '\n';
    return 0;
}