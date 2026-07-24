#include "test-framework.hpp"

#include "endterm-2023.hpp"

#include <algorithm>
#include <string>
#include <vector>

namespace aud::tests {
namespace {

using namespace aud::endterm_2023;

std::vector<int> listValues(exercise_10::DoublyLinkedList& list) {
    std::vector<int> values;
    exercise_10::DoublyLinkedList::Node* previous = nullptr;
    for (auto* node = list.head; node != nullptr; node = node->next) {
        expect(node->prev == previous, "prev-Pointer zeigt auf den falschen Knoten");
        values.push_back(node->val);
        previous = node;
    }
    return values;
}

}

void registerEndterm2023(Registry& registry) {
    registry.add("endterm-2023", "Exercise 09: Beispiel mit zwei Fragezeichen", [] {
        auto actual = exercise_09::listPatterns("0?1?");
        std::sort(actual.begin(), actual.end());
        const std::vector<std::string> expected{"0010", "0011", "0110", "0111"};
        expect(actual == expected, "die vier Muster aus dem Klausurbeispiel fehlen");
    });

    registry.add("endterm-2023", "Exercise 09: keine und nur Fragezeichen", [] {
        expect(exercise_09::listPatterns("101") == std::vector<std::string>{"101"},
               "ein String ohne '?' muss unverändert zurückkommen");
        auto actual = exercise_09::listPatterns("??");
        std::sort(actual.begin(), actual.end());
        expect(actual == std::vector<std::string>({"00", "01", "10", "11"}),
               "für zwei '?' werden alle vier Belegungen benötigt");
    });

    registry.add("endterm-2023", "Exercise 10: Baumhöhe zählt Kanten", [] {
        using exercise_10::TreeNode;
        TreeNode leaf{7};
        expectEqual(exercise_10::treeHeight(&leaf), 0, "Höhe eines Blatts");

        TreeNode deep{4};
        TreeNode middle{3, nullptr, &deep};
        TreeNode left{2};
        TreeNode root{1, &left, &middle};
        expectEqual(exercise_10::treeHeight(&root), 2, "Höhe des unbalancierten Baums");
    });

    registry.add("endterm-2023", "Exercise 10: Summe mehrerer tiefster Blätter", [] {
        using exercise_10::TreeNode;
        TreeNode a{4};
        TreeNode b{5};
        TreeNode c{6};
        TreeNode left{2, &a, &b};
        TreeNode right{3, nullptr, &c};
        TreeNode root{1, &left, &right};
        expectEqual(exercise_10::deepestLeavesSum(&root), 15,
                    "Summe der drei Blätter auf Tiefe 2");

        TreeNode deeper{9};
        c.right = &deeper;
        expectEqual(exercise_10::deepestLeavesSum(&root), 9,
                    "nur das nun tiefste Blatt darf zählen");
    });

    registry.add("endterm-2023", "Exercise 10: Einfügen an Kopf, Mitte und Ende", [] {
        exercise_10::DoublyLinkedList list;
        list.insertAt(20, 0);
        list.insertAt(10, 0);
        list.insertAt(40, 2);
        list.insertAt(30, 2);
        expectSequence(listValues(list), {10, 20, 30, 40}, "Listeninhalt");
        expectEqual(list.warningCount, 0, "Anzahl Warnungen");
    });

    registry.add("endterm-2023", "Exercise 10: ungültiges Einfügen ist atomar", [] {
        exercise_10::DoublyLinkedList list;
        auto* first = new exercise_10::DoublyLinkedList::Node(1);
        auto* second = new exercise_10::DoublyLinkedList::Node(2);
        first->next = second;
        second->prev = first;
        list.head = first;

        list.insertAt(9, 4);
        expectSequence(listValues(list), {1, 2}, "Liste nach zu großem Index");
        expectEqual(list.warningCount, 1, "Anzahl Warnungen");

        list.insertAt(9, -1);
        expectSequence(listValues(list), {1, 2}, "Liste nach negativem Index");
        expectEqual(list.warningCount, 2, "Anzahl Warnungen");
    });
}

}
