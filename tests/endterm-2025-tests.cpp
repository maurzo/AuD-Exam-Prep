#include "test-framework.hpp"

#include "endterm-2025.hpp"

#include <algorithm>
#include <cstdlib>
#include <set>
#include <vector>

namespace aud::tests {
namespace {

using namespace aud::endterm_2025;

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

bool pairUsesInput(const std::pair<int, int>& pair, const std::vector<int>& input) {
    return pair.first != pair.second
        && std::find(input.begin(), input.end(), pair.first) != input.end()
        && std::find(input.begin(), input.end(), pair.second) != input.end();
}

}

void registerEndterm2025(Registry& registry) {
    registry.add("endterm-2025", "Exercise 06: Knoten mit exakt zwei Kindern", [] {
        using exercise_06::TreeNode;
        TreeNode a{1};
        TreeNode b{2};
        TreeNode c{3};
        TreeNode left{5, &a, &b};
        TreeNode right{6, &c, nullptr};
        TreeNode root{7, &left, &right};
        expectEqual(exercise_06::count(&root), 2, "Anzahl voller Knoten");
        expectEqual(exercise_06::count(nullptr), 0, "leerer Baum");
    });

    registry.add("endterm-2025", "Exercise 06: traurige Knoten verwenden strikten Vergleich", [] {
        using exercise_06::TreeNode;
        TreeNode deep{1};
        TreeNode left{1, &deep, nullptr};
        TreeNode right{-1};
        TreeNode root{0, &left, &right};
        expectEqual(exercise_06::countSadNodes(&root), 2,
                    "nur Tiefe 2 > 1 und Tiefe 1 > -1 sind traurig");
    });

    registry.add("endterm-2025", "Exercise 07: Indizes rekursiv extrahieren", [] {
        using exercise_07::ListNode;
        ListNode n4{40};
        ListNode n3{30, &n4};
        ListNode n2{20, &n3};
        ListNode n1{10, &n2};
        ListNode i2{2};
        ListNode i0{0, &i2};

        auto* result = exercise_07::extract(&n1, &i0);
        expectSequence(valuesOf(result), {10, 30}, "extrahierte Werte");
        expectSequence(valuesOf(&n1), {10, 20, 30, 40}, "unveränderte Werteliste");
        expectSequence(valuesOf(&i0), {0, 2}, "unveränderte Indexliste");
        expect(result != &n1 && result != &n3, "Ergebnis muss neue Knoten besitzen");
        deleteList(result);
    });

    registry.add("endterm-2025", "Exercise 07: leere Indexliste", [] {
        exercise_07::ListNode value{7};
        expect(exercise_07::extract(&value, nullptr) == nullptr,
               "ohne Indizes muss die Ergebnisliste leer sein");
    });

    registry.add("endterm-2025", "Exercise 10: zweiter unterschiedlicher Abstand", [] {
        const std::vector<int> input{8, 3, 5, 2, 10, 4};
        const auto result = exercise_10::kClosestPair(input, 2);
        expect(result.has_value(), "ein 2-closest pair muss existieren");
        expect(pairUsesInput(*result, input), "Paar enthält einen fremden oder gleichen Wert");
        expectEqual(std::abs(result->first - result->second), 2,
                    "zweiter unterschiedlicher Abstand");
    });

    registry.add("endterm-2025", "Exercise 10: erster Abstand und nicht existentes k", [] {
        const std::vector<int> input{1, 4, 10};
        const auto first = exercise_10::kClosestPair(input, 1);
        expect(first.has_value(), "ein kleinstes Paar muss existieren");
        expectEqual(std::abs(first->first - first->second), 3, "kleinster Abstand");
        expect(!exercise_10::kClosestPair(input, 4).has_value(),
               "es gibt nur drei unterschiedliche Abstände");
    });
}

}
