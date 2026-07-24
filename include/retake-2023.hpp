#pragma once

#include <string_view>

namespace aud::retake_2023 {

namespace exercise_09 {
bool validSequence(std::string_view s);
}

namespace exercise_10 {

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

int sumOfLeftLeaves(TreeNode* node);
bool isSameTree(TreeNode* a, TreeNode* b);
bool isSubtreeOf(TreeNode* root, TreeNode* subRoot);

struct DoublyLinkedList {
    struct Node {
        int val;
        Node* prev = nullptr;
        Node* next = nullptr;
        explicit Node(int v) : val(v) {}
    };

    Node* head = nullptr;
    int warningCount = 0;

    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    void warn() { ++warningCount; }
    void deleteAt(int pos);
};

}
}
