#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

// task1: reverse s1, then check if s1 is a substr of s2 using KMP
vector<int> computeLPS(const string& str) {
    int m = str.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (str[i] == str[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

bool kmp(const string& s2, const string& s1) {
    int n = s2.length();
    int m = s1.length();
    vector<int> lps = computeLPS(s1);

    int i = 0;  // Index for text[]
    int j = 0;  // Index for pattern[]

    while (i < n) {
        if (s1[j] == s2[i]) {
            i++;
            j++;
        }

        if (j == m) {
            // Pattern found
            return true;
        }

        if (i < n && s1[j] != s2[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    // Pattern not found
    return false;
}

void reverse_str(string& str){
    if (str.size() == 0) return;
    int l = 0;
    int r = str.size() - 1;
    while (l < r){
        char tmp = str[l];
        str[l] = str[r];
        str[r] = tmp;
        l++;
        r--;
    }
}

bool check_permutation(string& s1, string& s2){
    reverse_str(s1);
    // cout << s1;
    return kmp(s2, s1);
}


// task2:

void dfs(int row, int & ans, vector<int>& col, vector<int>& on_path, \
 vector<int>& diag1, vector<int>& diag2, vector<int> queens){

    if (row == 8) {
        int cnt = 0;
        for (int i = 0; i < 8; ++i)
            if (col[i] != queens[i]){
                cnt++;
            }
        ans = min(ans, cnt);
        return;
    }

    for (int c = 0; c < 8; ++c) {
        int rc = row - c + 8 - 1;
        if (!on_path[c] && !diag1[row + c] && !diag2[rc]) {
            col[row] = c;
            on_path[c] = diag1[row + c] = diag2[rc] = true;
            dfs(row + 1, ans, col, on_path, diag1, diag2, queens);
            on_path[c] = diag1[row + c] = diag2[rc] = false; 
        }

    }
 }

int min_moves(vector<int>& queens){
    int ans = 7;
    vector<int> col(8), on_path(8), diag1(15), diag2(15);
    for (int i = 0; i< 8; i++) {
        queens[i]--;
    }
    dfs(0, ans, col, on_path, diag1, diag2, queens);
    return ans;
}


void test5() {
    string s1 = "ab";
    string s2 = "eidboaoo";
    cout << check_permutation(s1, s2) << endl;

    s1 = "ab";
    s2 = "eidbaoo";
    cout << check_permutation(s1, s2) << endl;

    s1 = "aba";
    s2 = "eidbbaabaoo";
    cout << check_permutation(s1, s2) << endl;

    s1 = "ababbb";
    s2 = "eidbbababbaoo";
    cout << check_permutation(s1, s2) << endl;

    s1 = "ababbghkhewdkuki";
    s2 = "eidbabbabaoo";
    cout << check_permutation(s1, s2) << endl;

    cout << "----------" << endl;
    std::vector<int> queens = {1,2,3,4,5,6,7,8};
    cout << min_moves(queens) << endl;
    queens = {1,1,1,1,1,1,1,1};
    cout << min_moves(queens) << endl;
    queens = {1,5,8,6,3,7,2,4};
    cout << min_moves(queens) << endl;
    queens = {1,5,8,6,5,7,2,4};
    cout << min_moves(queens) << endl;
    queens = {5,1,8,6,5,7,2,4};
    cout << min_moves(queens) << endl;
}



