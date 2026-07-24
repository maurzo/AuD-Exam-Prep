#pragma once

#include <functional>
#include <queue>
#include <vector>

namespace aud::retake_2025 {

namespace exercise_06 {
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

struct ReturnValue {
    int numLeaves;
    int numHappyNodes;
};

int countLeaves(TreeNode* node);
ReturnValue count(TreeNode* node);
int countHappyNodes(TreeNode* node);
}

namespace exercise_07 {
struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

ListNode* merge(ListNode* a, ListNode* b);
int locate(ListNode* list, int x);
void swap(ListNode* node, int i, int j);
}

namespace exercise_10 {
class MedianStream {
public:
    void insert(double x);
    double getMedian() const;

private:
    std::priority_queue<double> lower;
    std::priority_queue<double, std::vector<double>, std::greater<>> upper;
};
}

}
