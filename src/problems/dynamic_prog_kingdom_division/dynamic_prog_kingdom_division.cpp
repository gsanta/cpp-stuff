#include <bits/stdc++.h>
#include <set>
#include <iterator>
#include <map>
#include <queue>
#include <stack>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

int kingdomDivision(int n, vector<vector<int>> roads) {
    map<int, vector<int>> edges;
    map<int, int> degree;
    
    // this map contains the calculated count for the sub-tree where key is the root
    // second parameter is a two element vector
    // [0] contains the safe variations where node and it's parent have different colors
    // [1] contains the safe variations where node and it's parent have same color
    map<int, vector<long long>> count;

    long long mod = 1E9L + 7L;
    const int FALSE = 0;
    const int TRUE = 1;

    // Initialize data structures
    for (int i = 0; i < n; ++i) {
        edges[i] = {};
        degree[i] = 0;
        count[i] = {1, 1};
    }

    // Build the graph and calculate node degrees, make the node indexes zero based
    for (const auto& road : roads) {
        int node1 = road[0] - 1;
        int node2 = road[1] - 1;
        edges[node1].push_back(node2);
        edges[node2].push_back(node1);
        degree[node1]++;
        degree[node2]++;
    }

    int root = 0;

    // Identify leaf nodes
    queue<int> leaves;
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1 && i != 0) {
            leaves.push(i);
        }
    }

    // Traverse the tree from bottom up (processing leaves first and then removing those leaves from the tree) until there is only the root left
    // Every time we process the leaf 'y' it contains the count for the two cases
    // case 1: safe variations where y and it's parent x has the same color
    // case 2: safe variations where y and it's parent x has different colors
    while(true) {
        int y = leaves.front();
        leaves.pop();

        // when y was still a parent we stored the opposite value in it's 'false' count, namely it contained the count of those sub-arrays
        // that are not valid when y and parent differs in colors. With this subtraction we fix the issue because we subtract from the total count the invalid count
        count[y][FALSE] = count[y][TRUE] - count[y][FALSE];
        count[y][FALSE] += mod;
        count[y][FALSE] %= mod;

        // Check if it's the root
        if (degree[y] == 0) {
            root = y;
            break;
        } else {
            int x = edges[y][0];

            // maintain the adjacency matrix
            edges.erase(y);
            edges[x].erase(std::find(edges[x].begin(), edges[x].end(), y));
            degree[x] -= 1;

            if (degree[x] == 1 || degree[x] == 0) {
                leaves.push(x);
            }

            // if parent x and grandparent have the same color any sub-array is valid (since parent and grandparent already make a pair)
            count[x][TRUE] *= (count[y][TRUE] + count[y][FALSE]);
            // we store here temporarily the opposite count (if parent and grandparent have different colors, node and parent have to have the same)
            // this will be fixed when parent becomes the actual node and we subtract the invalid count from total (see code a little bit above) 
            count[x][FALSE] *= (count[y][FALSE]);

            count[x][TRUE] %= mod;
            count[x][FALSE] %= mod;
        }
    }

    // since there are 2 colors the whole process can be done with flipping the colors so we double the count
    return (2L * count[root][FALSE]) % mod;
}

int main()
{
    ifstream file("example2.txt");

    string n_temp;
    getline(file, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> roads(n - 1);

    for (int i = 0; i < n - 1; i++) {
        roads[i].resize(2);

        string roads_row_temp_temp;
        getline(file, roads_row_temp_temp);

        vector<string> roads_row_temp = split(rtrim(roads_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int roads_row_item = stoi(roads_row_temp[j]);

            roads[i][j] = roads_row_item;
        }
    }

    file.close();

    int result = kingdomDivision(n, roads);

    std::cout << "result: " << result << std::endl;

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