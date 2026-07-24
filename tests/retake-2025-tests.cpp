#include "test-framework.hpp"

#include "retake-2025.hpp"

#include <set>
#include <vector>

namespace aud::tests {
namespace {

using namespace aud::retake_2025;

exercise_07::ListNode* makeList(const std::vector<int>& values,
                                std::vector<exercise_07::ListNode*>* nodes = nullptr) {
    exercise_07::ListNode* head = nullptr;
    exercise_07::ListNode* tail = nullptr;
    for (int value : values) {
        auto* node = new exercise_07::ListNode(value);
        if (head == nullptr) head = node;
        else tail->next = node;
        tail = node;
        if (nodes != nullptr) nodes->push_back(node);
    }
    return head;
}

std::vector<int> valuesOf(exercise_07::ListNode* node) {
    std::vector<int> values;
    for (; node != nullptr; node = node->next) values.push_back(node->val);
    return values;
}

void deleteList(exercise_07::ListNode* node) {
    while (node != nullptr) {
        auto* next = node->next;
        delete node;
        node = next;
    }
}

}

void registerRetake2025(Registry& registry) {
    registry.add("retake-2025", "Exercise 06: Blattknoten zählen", [] {
        using exercise_06::TreeNode;
        TreeNode a{1};
        TreeNode b{2};
        TreeNode c{3};
        TreeNode right{4, &b, &c};
        TreeNode root{5, &a, &right};
        expectEqual(exercise_06::countLeaves(&root), 3, "Anzahl Blätter");
        expectEqual(exercise_06::countLeaves(&a), 1, "ein Blatt");
        expectEqual(exercise_06::countLeaves(nullptr), 0, "leerer Baum");
    });

    registry.add("retake-2025", "Exercise 06: Blatt- und Glückszahl gemeinsam berechnen", [] {
        using exercise_06::TreeNode;
        TreeNode left{1};
        TreeNode rightLeft{1};
        TreeNode rightRight{5};
        TreeNode right{2, &rightLeft, &rightRight};
        TreeNode root{3, &left, &right};

        const auto result = exercise_06::count(&root);
        expectEqual(result.numLeaves, 3, "Blattzahl der Wurzel");
        expectEqual(result.numHappyNodes, 4, "glückliche Knoten");
        expectEqual(exercise_06::countHappyNodes(&root), 4, "Wrapper countHappyNodes");
    });

    registry.add("retake-2025", "Exercise 07: zwei sortierte Listen ohne neue Knoten", [] {
        std::vector<exercise_07::ListNode*> aNodes;
        std::vector<exercise_07::ListNode*> bNodes;
        auto* a = makeList({1, 4, 8}, &aNodes);
        auto* b = makeList({2, 3, 9}, &bNodes);
        auto* result = exercise_07::merge(a, b);
        expectSequence(valuesOf(result), {1, 2, 3, 4, 8, 9}, "verschmolzene Liste");

        std::set<exercise_07::ListNode*> originals;
        originals.insert(aNodes.begin(), aNodes.end());
        originals.insert(bNodes.begin(), bNodes.end());
        int visited = 0;
        for (auto* node = result; node != nullptr; node = node->next) {
            expect(originals.contains(node), "merge hat einen neuen Knoten angelegt");
            ++visited;
        }
        expectEqual(visited, 6, "Anzahl wiederverwendeter Knoten");
        deleteList(result);
    });

    registry.add("retake-2025", "Exercise 07: merge mit leerer Liste", [] {
        auto* list = makeList({1, 2});
        expect(exercise_07::merge(nullptr, list) == list,
               "leere linke Liste muss die rechte Liste ergeben");
        deleteList(list);
    });

    registry.add("retake-2025", "Exercise 07: Einfügeposition ohne Sortieren", [] {
        exercise_07::ListNode n4{4};
        exercise_07::ListNode n3{9, &n4};
        exercise_07::ListNode n2{1, &n3};
        exercise_07::ListNode n1{7, &n2};
        expectEqual(exercise_07::locate(&n1, 5), 2, "Index von 5");
        expectEqual(exercise_07::locate(&n1, 0), 0, "Index des neuen Minimums");
        expectEqual(exercise_07::locate(&n1, 10), 4, "Index des neuen Maximums");
        expectSequence(valuesOf(&n1), {7, 1, 9, 4}, "Eingabeliste darf sich nicht ändern");
    });

    registry.add("retake-2025", "Exercise 07: Werte an zwei Indizes tauschen", [] {
        exercise_07::ListNode n4{40};
        exercise_07::ListNode n3{30, &n4};
        exercise_07::ListNode n2{20, &n3};
        exercise_07::ListNode n1{10, &n2};
        exercise_07::swap(&n1, 1, 3);
        expectSequence(valuesOf(&n1), {10, 40, 30, 20}, "Tausch von Index 1 und 3");
    });

    registry.add("retake-2025", "Exercise 07: out-of-bounds-Tausch bleibt atomar", [] {
        exercise_07::ListNode n3{30};
        exercise_07::ListNode n2{20, &n3};
        exercise_07::ListNode n1{10, &n2};
        exercise_07::swap(&n1, 0, 5);
        expectSequence(valuesOf(&n1), {10, 20, 30}, "Liste bei ungültigem j");
    });

    registry.add("retake-2025", "Exercise 10: Median nach jedem Insert", [] {
        exercise_10::MedianStream stream;
        stream.insert(5);
        expectNear(stream.getMedian(), 5, "Median nach [5]");
        stream.insert(1);
        expectNear(stream.getMedian(), 3, "Median nach [5,1]");
        stream.insert(10);
        expectNear(stream.getMedian(), 5, "Median nach [5,1,10]");
        stream.insert(4);
        expectNear(stream.getMedian(), 4.5, "Median nach [5,1,10,4]");
    });

    registry.add("retake-2025", "Exercise 10: negative Werte und Duplikate", [] {
        exercise_10::MedianStream stream;
        for (double value : {-2.0, -2.0, 7.0, 100.0, 0.0}) stream.insert(value);
        expectNear(stream.getMedian(), 0, "Median von [-2,-2,0,7,100]");
    });
}

}
