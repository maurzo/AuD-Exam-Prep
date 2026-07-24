#include "test-framework.hpp"

#include "endterm-2024.hpp"

#include <array>
#include <climits>
#include <string>
#include <vector>

namespace aud::tests {
namespace {

using namespace aud::endterm_2024;

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

void registerEndterm2024(Registry& registry) {
    registry.add("endterm-2024", "Exercise 01: Ziffernhäufigkeiten von pi", [] {
        const std::string digits = "1415926535";
        auto pi = [&digits](int i) { return digits.at(static_cast<std::size_t>(i - 1)) - '0'; };
        const std::array<int, 10> expected{0, 2, 1, 1, 1, 3, 1, 0, 0, 1};
        expect(exercise_01::countDigits(10, pi) == expected,
               "Häufigkeiten für 1415926535 sind falsch");

        const std::array<int, 10> empty{};
        expect(exercise_01::countDigits(0, pi) == empty,
               "für n=0 müssen alle Zähler null sein");
    });

    registry.add("endterm-2024", "Exercise 05: Wurzelpfade enden an jedem Knoten", [] {
        using exercise_05::TreeNode;
        TreeNode zero{0};
        TreeNode otherFive{5};
        TreeNode root{5, &zero, &otherFive};
        expectEqual(exercise_05::rootPaths(&root, 5), 2,
                    "Pfade [5] und [5,0] ab der Wurzel");
        expectEqual(exercise_05::rootPaths(nullptr, 0), 0, "leerer Baum");
    });

    registry.add("endterm-2024", "Exercise 05: alle Abwärtspfade", [] {
        using exercise_05::TreeNode;
        TreeNode zero{0};
        TreeNode otherFive{5};
        TreeNode root{5, &zero, &otherFive};
        expectEqual(exercise_05::totalPaths(&root, 5), 3,
                    "Pfade [5], [5,0] und rechter [5]-Knoten");
    });

    registry.add("endterm-2024", "Exercise 06: SearchData eines Suchbaums", [] {
        using exercise_06::TreeNode;
        TreeNode one{1};
        TreeNode three{3};
        TreeNode six{6};
        TreeNode two{2, &one, &three};
        TreeNode root{4, &two, &six};
        const auto data = exercise_06::traverse(&root);
        expectEqual(data.min, 1, "Minimum");
        expectEqual(data.max, 6, "Maximum");
        expectEqual(data.dist, 1, "kleinster Abstand");
    });

    registry.add("endterm-2024", "Exercise 06: kleinster Abstand über Teilbaumgrenze", [] {
        using exercise_06::TreeNode;
        TreeNode three{3};
        TreeNode fifteen{15};
        TreeNode twenty{20, &fifteen, nullptr};
        TreeNode root{10, &three, &twenty};
        expectEqual(exercise_06::minAbsDiff(&root), 5, "kleinster Abstand");

        TreeNode single{42};
        expectEqual(exercise_06::traverse(&single).dist, INT_MAX,
                    "ein einzelner Knoten hat kein Knotenpaar");
    });

    registry.add("endterm-2024", "Exercise 09: Umfang und unverändertes Grid", [] {
        const std::vector<std::vector<int>> grid{
            {0, 1, 0},
            {1, 1, 0},
            {0, 1, 1},
        };
        const auto original = grid;
        expectEqual(exercise_09::perimeter(grid, 1, 1), 12, "Umfang der L-Insel");
        expect(grid == original, "grid wurde verändert");
    });

    registry.add("endterm-2024", "Exercise 09: einzelnes Landfeld", [] {
        const std::vector<std::vector<int>> grid{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
        expectEqual(exercise_09::perimeter(grid, 1, 1), 4, "Umfang eines Feldes");
    });

    registry.add("endterm-2024", "Exercise 10: Klausurbeispiel und neue Liste", [] {
        using exercise_10::ListNode;
        ListNode n7{0};
        ListNode n6{2, &n7};
        ListNode n5{5, &n6};
        ListNode n4{4, &n5};
        ListNode n3{0, &n4};
        ListNode n2{1, &n3};
        ListNode n1{3, &n2};
        ListNode head{0, &n1};

        auto* result = exercise_10::merge(&head);
        expectSequence(valuesOf(result), {4, 11}, "zusammengefasste Liste");
        expectSequence(valuesOf(&head), {0, 3, 1, 0, 4, 5, 2, 0},
                       "unveränderte Eingabeliste");
        expect(result != &head && result != &n1, "Ergebnis muss eine neue Liste sein");
        deleteList(result);
    });

    registry.add("endterm-2024", "Exercise 10: ein Abschnitt", [] {
        using exercise_10::ListNode;
        ListNode end{0};
        ListNode value{-3, &end};
        ListNode head{0, &value};
        auto* result = exercise_10::merge(&head);
        expectSequence(valuesOf(result), {-3}, "Liste mit einem Abschnitt");
        deleteList(result);
    });
}

}
