#include <iostream>
#include <vector>
#include "main.h"

using namespace std;

// the index of first element >= target
int lower_bound(vector<int>& nums, int target) {
    int n = nums.size();
    int l = 0;
    int r = n - 1;
    while (l <= r){
        int mid = (l + r) / 2;
        if (nums[mid] >= target){
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }

    return l;
}

// find start and end position of target in a sorted array
// return [-1, -1] if target not found
vector<int> find_position_in_array(vector<int>& nums, int target){
    vector<int> ans(2);
    int n = nums.size();
    int ans1 = lower_bound(nums, target);
    if (ans1 == n || nums[ans1] != target){
        ans[0] = -1;
        ans[1] = -1;
    }
    else{
        ans[0] = lower_bound(nums,target);
        ans[1] = lower_bound(nums, target+1) - 1;
    }
    return ans;
}

// given a sorted matrix, return if target is in matrix
bool find_position_in_matrix(vector<vector<int>>& matrix, int target){
    int m = matrix.size();
    int n = matrix[0].size();
    int l = 0;
    int r = m * n - 1;
    while (l <= r){
        int mid = (l + r) / 2;
        if(matrix[mid/n][mid%n] >= target){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    if (l == m * n) {
        return false;
    }
    if (matrix[l/n][l%n] == target){
        return true;
    }
    return false;
}

// test for module2
void test2(){
    vector<int> nums = {4,9,10,13,17,17,19,21};
    int target = 17;
    vector<int> ans = find_position_in_array(nums, target);
    std::cout << ans[0] << " " << ans[1] << std::endl;

    nums = {2,4,6,8,10,14,16};
    target = 12;
    ans = find_position_in_array(nums, target);
    std::cout << ans[0] << " " << ans[1] << std::endl;

    nums = {};
    target = 0;
    ans = find_position_in_array(nums, target);
    std::cout << ans[0] << " " << ans[1] << std::endl;

    nums = {2,4,6,8,10,14,16};
    target = 1;
    ans = find_position_in_array(nums, target);
    std::cout << ans[0] << " " << ans[1] << std::endl;

    nums = {2,4,6,8,10,16,16};
    target = 16;
    ans = find_position_in_array(nums, target);
    std::cout << ans[0] << " " << ans[1] << std::endl;

    nums = {2,4,6,8,10,16,16};
    target = 18;
    ans = find_position_in_array(nums, target);
    std::cout << ans[0] << " " << ans[1] << std::endl;

    nums = {2,2,2,8,10,14,16};
    target = 2;
    ans = find_position_in_array(nums, target);
    std::cout << ans[0] << " " << ans[1] << std::endl;

    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,40}};
    target = 3;
    bool res = find_position_in_matrix(matrix, target);
    std::cout << res << std::endl;

    matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,40}};
    target = 13;
    res = find_position_in_matrix(matrix, target);
    std::cout << res << std::endl;
    
    matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,40}};
    target = 1;
    res = find_position_in_matrix(matrix, target);
    std::cout << res << std::endl;

    matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,40}};
    target = 40;
    res = find_position_in_matrix(matrix, target);
    std::cout << res << std::endl;

    matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,40}};
    target = 41;
    res = find_position_in_matrix(matrix, target);
    std::cout << res << std::endl;

    matrix = {{}};
    target = 41;
    res = find_position_in_matrix(matrix, target);
    std::cout << res << std::endl;
}