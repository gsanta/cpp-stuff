#include <bits/stdc++.h>
#include <set>
#include <iterator>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'equal' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int equal(vector<int> arr) {

    int minVal = 1000;

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    int minOperations = 2E6;

    for (int i = 0; i < 5; i++) {
        int currMinOperations = 0;

        for (int j = 0; j < arr.size(); j++) {
            int x = arr[j];
            int t = x - minVal;

            currMinOperations += t / 5;
            t = t % 5;
            currMinOperations += t / 2;
            currMinOperations += t % 2;
        } 

        if (currMinOperations < minOperations) {
            minOperations = currMinOperations;
        }
        minVal -= 1;
    }

    return minOperations;
}

// int equal(vector<int> arr) {
//     std::set<int> set;
//     int iter = 0;
    
//     for (int i = 0; i < arr.size(); i++) {
//         set.insert(arr[i]);
//     }
    
//     vector<int> amounts = { 1, 2, 5 };

//     vector<int> secondaryAmounts = { 3, 4 };

//     int fullAmount = 0;

//     vector<int> debugAmounts;

    
//     while(set.size() > 1) {
//         int min = *set.begin();
//         int selectedAmount = 0;        
//         for (int i = 0; i < amounts.size(); i++) {
//             const bool isIn = set.find(min + amounts[i]) != set.end();
            
//             if (isIn) {
//                 selectedAmount = amounts[i];
//                 iter++;

//                 break;
//             }
//         }

//         if (selectedAmount == 0) {
//             for (int i = 0; i < secondaryAmounts.size(); i++) {
//                 const bool isIn = set.find(min + secondaryAmounts[i]) != set.end();
                
//                 if (isIn) {
//                     selectedAmount = secondaryAmounts[i];
//                     iter += 2;

//                     break;
//                 }
//             }
//         }

//         if (selectedAmount == 0) {
//             selectedAmount = 5;
//             iter++;
//         }

//         fullAmount += selectedAmount;
        
        
//         std::set<int> tempSet;

//         const bool contains = set.find(min + selectedAmount) != set.end();

//         int skipValue = 0;
//         if (contains) {
//             skipValue = min + selectedAmount;
//         } else {
//             skipValue = *std::next(set.begin(), 1);
//         }
        
//         for(auto it = set.begin(); it != set.end(); it++) {
//             if (*it == skipValue) {
//                 tempSet.insert(skipValue);
//             } else {
//                 tempSet.insert(*it + selectedAmount);
//             }
//         }

//         if (tempSet.size() < set.size()) {
//             debugAmounts.push_back(fullAmount);
//         }
        
//         set = tempSet;
        
//         std::cout << "set size: " << set.size() << " min: " << min << std::endl;
//     }
    
//     return iter;
// }


int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    // string t_temp;
    // getline(cin, t_temp);

    // int t = stoi(ltrim(rtrim(t_temp)));

    // for (int t_itr = 0; t_itr < t; t_itr++) {
    //     string n_temp;
    //     getline(cin, n_temp);

    //     int n = stoi(ltrim(rtrim(n_temp)));

    //     string arr_temp_temp;
    //     getline(cin, arr_temp_temp);

    //     vector<string> arr_temp = split(rtrim(arr_temp_temp));

    //     vector<int> arr(n);

    //     for (int i = 0; i < n; i++) {
    //         int arr_item = stoi(arr_temp[i]);

    //         arr[i] = arr_item;
    //     }

    //     int result = equal(arr);

    //     fout << result << "\n";
    // }

    // fout.close();

    vector<int> arr = {
        2, 2, 3, 7
        // 761, 706, 697, 212, 97, 845, 151, 637, 102, 165, 200, 34, 912, 445, 435, 53, 12, 255, 111, 565, 816, 632, 534, 617, 18, 786, 790, 802, 253, 502, 602, 15, 208, 651, 227, 305, 848, 730, 294, 303, 895, 846, 337, 159, 291, 125, 565, 655, 380, 28, 221, 549, 13, 107, 166, 31, 245, 308, 185, 498, 810, 139, 865, 370, 790, 444, 27, 639, 174, 321, 294, 421, 168, 631, 933, 811, 756, 498, 467, 137, 878, 40, 686, 891, 499, 204, 274, 744, 512, 460, 242, 674, 599, 108, 396, 742, 552, 423, 733, 79, 96, 27, 852, 264, 658, 785, 76, 415, 635, 895, 904, 514, 935, 942, 757, 434, 498, 32, 178, 10, 844, 772, 36, 795, 880, 432, 537, 785, 855, 270, 864, 951, 649, 716, 568, 308, 854, 996, 75, 489, 891, 331, 355, 178, 273, 113, 612, 771, 497, 142, 133, 341, 914, 521, 488, 147, 953, 26, 284, 160, 648, 500, 463, 298, 568, 31, 958, 422, 379, 385, 264, 622, 716, 619, 800, 341, 732, 764, 464, 581, 258, 949, 922, 173, 470, 411, 672, 423, 789, 956, 583, 789, 808, 46, 439, 376, 430, 749, 151

        // 53, 361, 188, 665, 786, 898, 447, 562, 272, 123, 229, 629, 670, 848, 994, 54, 822, 46, 208, 17, 449, 302, 466, 832, 931, 778, 156, 39, 31, 777, 749, 436, 138, 289, 453, 276, 539, 901, 839, 811, 24, 420, 440, 46, 269, 786, 101, 443, 832, 661, 460, 281, 964, 278, 465, 247, 408, 622, 638, 440, 751, 739, 876, 889, 380, 330, 517, 919, 583, 356, 83, 959, 129, 875, 5, 750, 662, 106, 193, 494, 120, 653, 128, 84, 283, 593, 683, 44, 567, 321, 484, 318, 412, 712, 559, 792, 394, 77, 711, 977, 785, 146, 936, 914, 22, 942, 664, 36, 400, 857
    };

    int result = equal(arr);

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
