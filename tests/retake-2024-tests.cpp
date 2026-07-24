#include "test-framework.hpp"

#include "retake-2024.hpp"

#include <set>
#include <vector>

namespace aud::tests {
namespace {

using namespace aud::retake_2024;

exercise_10::ListNode* makeList(const std::vector<int>& values,
                                std::vector<exercise_10::ListNode*>* nodes = nullptr) {
    exercise_10::ListNode* head = nullptr;
    exercise_10::ListNode* tail = nullptr;
    for (int value : values) {
        auto* node = new exercise_10::ListNode(value);
        if (head == nullptr) head = node;
        else tail->next = node;
        tail = node;
        if (nodes != nullptr) nodes->push_back(node);
    }
    return head;
}

std::vector<int> valuesOf(exercise_10::ListNode* node) {
    std::vector<int> values;
    for (; node != nullptr; node = node->next) values.push_back(node->val);
    return values;
}

void deleteList(exercise_10::ListNode* node) {
    while (node != nullptr) {
        auto* next = node->next;
        delete node;
        node = next;
    }
}

}

void registerRetake2024(Registry& registry) {
    registry.add("retake-2024", "Exercise 01: nur exakt einmal vorkommende Werte", [] {
        const std::vector<int> input{4, 1, 4, 2, 3, 2, 8};
        const std::set<int> expected{1, 3, 8};
        expect(exercise_01::generate(input) == expected,
               "mehrfach vorkommende Werte müssen vollständig entfallen");
        expect(exercise_01::generate({}) == std::set<int>{}, "leere Eingabe");
    });

    registry.add("retake-2024", "Exercise 05: Rechtsrotation an der Wurzel", [] {
        using exercise_05::TreeNode;
        TreeNode transferred{19};
        TreeNode left{15, nullptr, &transferred};
        TreeNode right{31};
        TreeNode node{22, &left, &right};
        TreeNode* root = &node;
        left.parent = &node;
        right.parent = &node;
        transferred.parent = &left;

        exercise_05::rightRotate(&node, root);
        expect(root == &left, "root muss auf die neue Wurzel zeigen");
        expect(left.parent == nullptr, "neue Wurzel darf keinen parent haben");
        expect(left.right == &node && node.parent == &left,
               "alter Drehknoten muss rechtes Kind werden");
        expect(node.left == &transferred && transferred.parent == &node,
               "übertragener Teilbaum falsch verbunden");
        expect(node.right == &right && right.parent == &node,
               "unbeteiligter rechter Teilbaum wurde verändert");
    });

    registry.add("retake-2024", "Exercise 05: Rechtsrotation unterhalb der Wurzel", [] {
        using exercise_05::TreeNode;
        TreeNode transferred{25};
        TreeNode pivot{20, nullptr, &transferred};
        TreeNode node{30, &pivot, nullptr};
        TreeNode rootNode{50, &node, nullptr};
        TreeNode* root = &rootNode;
        node.parent = &rootNode;
        pivot.parent = &node;
        transferred.parent = &pivot;

        exercise_05::rightRotate(&node, root);
        expect(root == &rootNode, "globale Wurzel darf sich hier nicht ändern");
        expect(rootNode.left == &pivot && pivot.parent == &rootNode,
               "Elternknoten muss auf neue Teilbaumwurzel zeigen");
        expect(pivot.right == &node && node.parent == &pivot,
               "Rotation im Teilbaum ist unvollständig");
        expect(node.left == &transferred && transferred.parent == &node,
               "übertragener Teilbaum falsch verbunden");
    });

    registry.add("retake-2024", "Exercise 09: alle Hotelräume erreichbar", [] {
        const std::vector<std::vector<int>> rooms{{1}, {2}, {1, 3}, {}};
        expect(exercise_09::canVisitAllRooms(rooms), "Klausurbeispiel muss true ergeben");
        expect(exercise_09::canVisitAllRooms({{}}), "ein einzelner Raum ist erreichbar");
    });

    registry.add("retake-2024", "Exercise 09: verschlossener Raum bleibt unerreichbar", [] {
        const std::vector<std::vector<int>> rooms{{1, 1}, {}, {0}};
        expect(!exercise_09::canVisitAllRooms(rooms), "Raum 2 hat keinen erreichbaren Schlüssel");
    });

    registry.add("retake-2024", "Exercise 10: Gruppen zu Produkten verschmelzen", [] {
        std::vector<exercise_10::ListNode*> nodes;
        auto* head = makeList({4, 1, -2, -9, 3, 0, 2, 5, 1}, &nodes);
        exercise_10::merge(head, 3);
        expectSequence(valuesOf(head), {-8, 0, 10}, "Klausurbeispiel");
        expect(head == nodes[0] && head->next == nodes[3] && head->next->next == nodes[6],
               "jeweils erster Gruppenknoten muss erhalten bleiben");
        deleteList(head);
    });

    registry.add("retake-2024", "Exercise 10: Gruppen der Größe zwei", [] {
        auto* head = makeList({7, -1, 3, 2, 6, -2});
        exercise_10::merge(head, 2);
        expectSequence(valuesOf(head), {-7, 6, -12}, "zweites Klausurbeispiel");
        deleteList(head);
    });
}

}
