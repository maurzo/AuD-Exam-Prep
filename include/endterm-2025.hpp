#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace aud::endterm_2025 {

namespace exercise_06 {
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

int count(TreeNode* node);
int countSadNodes(TreeNode* node);
}

namespace exercise_07 {
struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int v, ListNode* p = nullptr) : val(v), next(p) {}
};

ListNode* extract(ListNode* node, ListNode* indices);
}

namespace exercise_10 {
std::optional<std::pair<int, int>> kClosestPair(std::vector<int> values, std::size_t k);
}

}
