#include "test-framework.hpp"

#include "retake-2023.hpp"

#include <vector>

namespace aud::tests {
namespace {

using namespace aud::retake_2023;

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

void fillList1234(exercise_10::DoublyLinkedList& list) {
    auto* n1 = new exercise_10::DoublyLinkedList::Node(1);
    auto* n2 = new exercise_10::DoublyLinkedList::Node(2);
    auto* n3 = new exercise_10::DoublyLinkedList::Node(3);
    auto* n4 = new exercise_10::DoublyLinkedList::Node(4);
    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;
    n3->next = n4;
    n4->prev = n3;
    list.head = n1;
}

}

void registerRetake2023(Registry& registry) {
    registry.add("retake-2023", "Exercise 09: korrekt geklammerte Ausdrücke", [] {
        expect(exercise_09::validSequence("([][])"), "gültiger Ausdruck abgelehnt");
        expect(exercise_09::validSequence(""), "leerer Ausdruck muss gültig sein");
        expect(exercise_09::validSequence("[()]"), "verschachtelter Ausdruck abgelehnt");
    });

    registry.add("retake-2023", "Exercise 09: fehlerhafte Ausdrücke", [] {
        expect(!exercise_09::validSequence("[()(])"), "Klausurbeispiel muss ungültig sein");
        expect(!exercise_09::validSequence("([)]"), "gekreuzte Klammern akzeptiert");
        expect(!exercise_09::validSequence("(()"), "offene Klammer am Ende akzeptiert");
        expect(!exercise_09::validSequence("]"), "schließende Klammer ohne Öffnung akzeptiert");
    });

    registry.add("retake-2023", "Exercise 10: Summe linker Blätter", [] {
        using exercise_10::TreeNode;
        TreeNode two{2};
        TreeNode four{4};
        TreeNode five{5};
        TreeNode right{3, &four, &five};
        TreeNode root{1, &two, &right};
        expectEqual(exercise_10::sumOfLeftLeaves(&root), 6, "linke Blätter 2 und 4");
        expectEqual(exercise_10::sumOfLeftLeaves(&two), 0,
                    "Wurzel ohne Elternknoten ist kein linkes Blatt");
    });

    registry.add("retake-2023", "Exercise 10: gleiche und ungleiche Bäume", [] {
        using exercise_10::TreeNode;
        TreeNode aLeft{2};
        TreeNode a{1, &aLeft, nullptr};
        TreeNode bLeft{2};
        TreeNode b{1, &bLeft, nullptr};
        expect(exercise_10::isSameTree(&a, &b), "identische Bäume nicht erkannt");

        bLeft.val = 3;
        expect(!exercise_10::isSameTree(&a, &b), "unterschiedliche Werte nicht erkannt");
        bLeft.val = 2;
        b.right = &bLeft;
        b.left = nullptr;
        expect(!exercise_10::isSameTree(&a, &b), "unterschiedliche Struktur nicht erkannt");
        expect(exercise_10::isSameTree(nullptr, nullptr), "zwei leere Bäume sind gleich");
    });

    registry.add("retake-2023", "Exercise 10: Teilbaum an tieferem Knoten", [] {
        using exercise_10::TreeNode;
        TreeNode four{4};
        TreeNode five{5};
        TreeNode two{2, &four, &five};
        TreeNode three{3};
        TreeNode root{1, &two, &three};

        TreeNode subLeft{4};
        TreeNode subRight{5};
        TreeNode sub{2, &subLeft, &subRight};
        expect(exercise_10::isSubtreeOf(&root, &sub), "vorhandener Teilbaum nicht erkannt");
        subRight.val = 9;
        expect(!exercise_10::isSubtreeOf(&root, &sub), "fremder Teilbaum akzeptiert");
    });

    registry.add("retake-2023", "Exercise 10: Löschen an Kopf, Mitte und Ende", [] {
        exercise_10::DoublyLinkedList list;
        fillList1234(list);
        list.deleteAt(0);
        expectSequence(listValues(list), {2, 3, 4}, "nach Löschen des Kopfs");
        list.deleteAt(1);
        expectSequence(listValues(list), {2, 4}, "nach Löschen in der Mitte");
        list.deleteAt(1);
        expectSequence(listValues(list), {2}, "nach Löschen des Endes");
        expectEqual(list.warningCount, 0, "Anzahl Warnungen");
    });

    registry.add("retake-2023", "Exercise 10: ungültiges Löschen ist atomar", [] {
        exercise_10::DoublyLinkedList list;
        fillList1234(list);
        list.deleteAt(4);
        expectSequence(listValues(list), {1, 2, 3, 4}, "nach zu großem Index");
        list.deleteAt(-1);
        expectSequence(listValues(list), {1, 2, 3, 4}, "nach negativem Index");
        expectEqual(list.warningCount, 2, "Anzahl Warnungen");
    });
}

}
