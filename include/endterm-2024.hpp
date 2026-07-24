#pragma once

#include <array>
#include <climits>
#include <functional>
#include <vector>

namespace aud::endterm_2024 {

namespace exercise_01 {
using PiDigit = std::function<int(int)>;
std::array<int, 10> countDigits(int n, const PiDigit& pi);
}

namespace exercise_05 {
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

int rootPaths(TreeNode* node, int targetSum);
int totalPaths(TreeNode* node, int targetSum);
}

namespace exercise_06 {
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

struct SearchData {
    int dist = INT_MAX;
    int min = 0;
    int max = 0;
};

SearchData traverse(TreeNode* node);
int minAbsDiff(TreeNode* root);
}

namespace exercise_09 {
int perimeter(const std::vector<std::vector<int>>& grid, int startRow, int startColumn);
}

namespace exercise_10 {
struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

ListNode* merge(ListNode* head);
}

}
