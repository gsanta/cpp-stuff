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

const int modulo = 1e9 + 7; // Define the modulo value
const int colorSafe = 0;    // Index for safe color
const int colorUnsafe = 1;  // Index for unsafe color

void dfs(int x, vector<vector<int>> &edges, vector<vector<long>> &counts, vector<int> &visited) {
    visited[x] = 1;
    // we initialize safeCount to 1, however for a single node it is always unsafe (if it's a single node graph it can not be made safe)
    // it would seem logical to initialize it to 0 however it would make the dynamic programming approach fail, because
    // we accumulate the unsafe variations for x via multiplying with it's childrens safe variations (see unsafeCount *= counts[y][colorSafe];) and multiplying with zero
    // would make that count stuck at zero
    // we later compensate for this surplus via subtracting the usafe variations from the safe variations (see safeCount -= unsafeCount)
    long safeCount = 1; 
    long unsafeCount = 1;

    for (int i = 0; i < edges[x].size(); i++) {
        int y = edges[x][i];
        if (visited[y]) {
            continue;
        }
        
        dfs(y, edges, counts, visited);

        // unsafeCount stores only the unsafe variations that are unsafe because x and y have different colors
        // we can get this number via iterating through the y children and multiplying with the safe variations
        // within the subtree of the y child (because we can make all of those safe variations unsafe when we choose for x a different color to y)
        unsafeCount *= counts[y][colorSafe];
        unsafeCount %= modulo;

        // safeCount accumulates all of the safe variations, because for every y child subtree
        // 1. `counts[y][unsafe]` is the count of unsafe variations where the subtree was unsafe because of y
        //      and it can be made safe if we choose x to have the color of y
        // 2. `counts[y][safe]` stores all of the safe variations available at the y subtree, it remains
        //      safe if we choose the x to have the color of y
        // 3. we add `counts[y][safe]` twice but this same amount will be subtracted after the for cycle (see safeCount -= unsafeCount)
        safeCount *= counts[y][colorSafe] + counts[y][colorSafe] + counts[y][colorUnsafe];
        safeCount %= modulo;
    }

    safeCount -= unsafeCount;
    safeCount += modulo;
    safeCount %= modulo;

    counts[x][colorSafe] = safeCount;
    counts[x][colorUnsafe] = unsafeCount;
}

int kingdomDivision(int n, vector<vector<int>> roads) {

    vector<vector<int>> edges;      // Adjacency list for the tree (edges[x] contains neighbors of node x)
    vector<vector<long>> counts;    // Dynamic programming array (counts[x][i] stores the count of colorings for node x with color i)
    vector<int> visited;            // Visited array (visited[x] is 1 if node x has been visited during DFS, 0 otherwise)

    edges.resize(n);
    counts.resize(n, vector<long>(2));
    visited.resize(n);

    // Construct the graph, make it zero base instead of 1 based
    for (auto x : roads) {
        x[0]--, x[1]--;
        edges[x[0]].push_back(x[1]);
        edges[x[1]].push_back(x[0]);
    }

    dfs(0, edges, counts, visited);

    // the algorithm calculated the safe variations from one color's perspective, to account for the variations with flipped colors
    // we have to multiply it with 2
    return (2 * counts[0][colorSafe]) % modulo;
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