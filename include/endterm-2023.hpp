#pragma once

#include <string>
#include <vector>

namespace aud::endterm_2023 {

namespace exercise_09 {
std::vector<std::string> listPatterns(std::string s);
}

namespace exercise_10 {

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

int treeHeight(TreeNode* node);
int deepestLeavesSum(TreeNode* node);

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
    void insertAt(int val, int pos);
};

}
}
