#include "test-framework.hpp"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>

namespace {

const std::set<std::string> kExams{
    "endterm-2023", "endterm-2024", "endterm-2025",
    "retake-2023", "retake-2024", "retake-2025",
};

void printAvailableExams() {
    std::cout << "Verfuegbare Klausuren:\n";
    for (const auto& exam : kExams) {
        std::cout << "  " << exam << '\n';
    }
}

bool startsWithTodo(const std::exception& error) {
    return std::string(error.what()).starts_with("TODO:");
}

}

int main(int argc, char** argv) {
    aud::tests::Registry registry;
    aud::tests::registerEndterm2023(registry);
    aud::tests::registerEndterm2024(registry);
    aud::tests::registerEndterm2025(registry);
    aud::tests::registerRetake2023(registry);
    aud::tests::registerRetake2024(registry);
    aud::tests::registerRetake2025(registry);

    if (argc == 2 && std::string(argv[1]) == "--list") {
        printAvailableExams();
        return 0;
    }

    std::set<std::string> selected;
    for (int i = 1; i < argc; ++i) {
        std::string exam = argv[i];
        if (!kExams.contains(exam)) {
            std::cerr << "Unbekannte Klausur: " << exam << "\n\n";
            printAvailableExams();
            return 2;
        }
        selected.insert(std::move(exam));
    }

    int passed = 0;
    int failed = 0;
    int open = 0;
    for (const auto& test : registry.cases()) {
        if (!selected.empty() && !selected.contains(test.exam)) continue;

        try {
            test.run();
            ++passed;
            std::cout << "[OK]    " << test.exam << " :: " << test.name << '\n';
        } catch (const std::exception& error) {
            if (startsWithTodo(error)) {
                ++open;
                std::cout << "[OFFEN] " << test.exam << " :: " << test.name
                          << " (" << error.what() << ")\n";
            } else {
                ++failed;
                std::cout << "[FEHLER] " << test.exam << " :: " << test.name
                          << " (" << error.what() << ")\n";
            }
        } catch (...) {
            ++failed;
            std::cout << "[FEHLER] " << test.exam << " :: " << test.name
                      << " (unbekannte Exception)\n";
        }
    }

    const int total = passed + failed + open;
    std::cout << "\nErgebnis: " << passed << '/' << total << " bestanden, "
              << failed << " fehlerhaft, " << open << " offen.\n";
    return failed == 0 && open == 0 ? 0 : 1;
}
