

#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'mandragora' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY H as parameter.
 */

long mandragora(vector<int> H) {
    sort(H.begin(), H.end());
    
    long max = 0;
    long sumToI = 0;
    
    
    for (int i = H.size() - 1; i >= 0; i--) {
        sumToI += H[i];
        
        if (max < sumToI * (i + 1)) {
            max = sumToI * (i + 1);
        } else {
            break;
        }
    }
    
    return max;
}

int main()
{
    ifstream file("example1.txt");

    string t_temp;
    getline(file, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(file, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string H_temp_temp;
        getline(file, H_temp_temp);

        vector<string> H_temp = split(rtrim(H_temp_temp));

        vector<int> H(n);

        for (int i = 0; i < n; i++) {
            int H_item = stoi(H_temp[i]);

            H[i] = H_item;
        }

        long result = mandragora(H);

        cout << result << "\n";
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
