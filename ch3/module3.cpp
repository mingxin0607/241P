#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// merge sort
string merge(const string& left, const string& right) {
    string result;
    int i = 0, j = 0;

    while (i < left.length() && j < right.length()) {
        if (left[i] < right[j]) {
            result += left[i++];
        } else {
            result += right[j++];
        }
    }

    while (i < left.length()) {
        result += left[i++];
    }

    while (j < right.length()) {
        result += right[j++];
    }

    return result;
}

string merge_sort(string s) {
    if (s.length() <= 1) {
        return s;
    }

    int middle = s.length() / 2;
    string left = s.substr(0, middle);
    string right = s.substr(middle);

    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}


// quick sort
int partition(string& arr, int low, int high) {
    char pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quick_sort(string& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// choose a sort method
void sort_string(string& str){

    str = merge_sort(str);
    // quick_sort(str, 0, str.size());

}

// group anagrams
vector<vector<string>> group_anagram(vector<string>& strings) {
    unordered_map<string, vector<string>> mp;

    for (string str : strings) {
        string str_copy = str;
        sort_string(str);
        mp[str].push_back(str_copy);
    }

    vector<vector<string>> res;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        res.push_back(it->second);
    }

    return res;
}

void test3(){
    vector<string> strs = {"bucket","rat","mango","tango","ogtan","tar"};
    vector<vector<string>> res = group_anagram(strs);
    for (auto& strs : res){
        for (auto& str : strs){
            cout << str << " ";
        }
        cout << endl;
    }


    strs = {"abc"};
    res = group_anagram(strs);
    for (auto& strs : res){
        for (auto& str : strs){
            cout << str << " ";
        }
        cout << endl;
    }

    strs = {""};
    res = group_anagram(strs);
    for (auto& strs : res){
        for (auto& str : strs){
            cout << str << " ";
        }
        cout << endl;
    }

    strs = {};
    res = group_anagram(strs);
    for (auto& strs : res){
        for (auto& str : strs){
            cout << str << " ";
        }
        cout << endl;
    }

    strs = {"feae","eaef","eew","weff","awewa","ffew","weff"};
    res = group_anagram(strs);
    for (auto& strs : res){
        for (auto& str : strs){
            cout << str << " ";
        }
        cout << endl;
    }
}