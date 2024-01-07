#include <bits/stdc++.h>
#include <set>
#include <iterator>
#include <map>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

vector<int> maxSubarray(vector<int> arr) {
    // max value when the current element is part of the max
    int maxWithCurr = 0;
    // global max, current element not necessarily part of it
    int maxGlobal = std::numeric_limits<int>::min();

    int maxSingleElement = std::numeric_limits<int>::min();
    int maxSubSequence = 0;

    for (int i = 0; i < arr.size(); i++) {
        int curr = arr[i];

        //subarray calculation
        maxWithCurr += curr;

        if (curr > maxWithCurr) {
            maxWithCurr = curr;
        }

        if (maxWithCurr >= maxGlobal) {
            maxGlobal = maxWithCurr;
        }

        // subsequence calculation
        if (curr > maxSingleElement) {
            maxSingleElement = curr;
        }

        if (curr > 0) {
            maxSubSequence += curr;
        }
    }

    return vector<int> { maxGlobal, maxSubSequence > 0 ? maxSubSequence : maxSingleElement };
}

int main()
{
    ifstream file("example2.txt");

    string t_temp;

    getline(file, t_temp);

    int n = stoi(ltrim(rtrim(t_temp)));


    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(file, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(file, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        vector<int> result = maxSubarray(arr);

        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];

            if (i != result.size() - 1) {
                cout << " ";
            }
        }

        cout << "\n";
    }

    file.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
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