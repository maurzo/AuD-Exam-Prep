#pragma once

#include <set>
#include <vector>

namespace aud::retake_2024 {

namespace exercise_01 {
std::set<int> generate(const std::vector<int>& values);
}

namespace exercise_05 {
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode* parent = nullptr;
};

void rightRotate(TreeNode* node, TreeNode*& root);
}

namespace exercise_09 {
bool canVisitAllRooms(const std::vector<std::vector<int>>& roomKeys);
}

namespace exercise_10 {
struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

void merge(ListNode* head, int k);
}

}
