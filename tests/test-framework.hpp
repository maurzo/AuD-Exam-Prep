#pragma once

#include <cmath>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace aud::tests {

struct TestCase {
    std::string exam;
    std::string name;
    std::function<void()> run;
};

class Registry {
public:
    template <typename Function>
    void add(std::string exam, std::string name, Function&& function) {
        cases_.push_back(
            {std::move(exam), std::move(name), std::forward<Function>(function)});
    }

    const std::vector<TestCase>& cases() const { return cases_; }

private:
    std::vector<TestCase> cases_;
};

inline void expect(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

template <typename Actual, typename Expected>
void expectEqual(const Actual& actual, const Expected& expected, const std::string& label) {
    if (!(actual == expected)) {
        std::ostringstream message;
        message << label << ": erwartet " << expected << ", erhalten " << actual;
        throw std::runtime_error(message.str());
    }
}

inline void expectNear(double actual, double expected, const std::string& label,
                       double tolerance = 1e-9) {
    if (std::abs(actual - expected) > tolerance) {
        std::ostringstream message;
        message << label << ": erwartet " << expected << ", erhalten " << actual;
        throw std::runtime_error(message.str());
    }
}

inline void expectSequence(const std::vector<int>& actual, const std::vector<int>& expected,
                           const std::string& label) {
    if (actual != expected) {
        auto print = [](const std::vector<int>& values) {
            std::ostringstream output;
            output << '[';
            for (std::size_t i = 0; i < values.size(); ++i) {
                if (i != 0) output << ',';
                output << values[i];
            }
            output << ']';
            return output.str();
        };
        throw std::runtime_error(
            label + ": erwartet " + print(expected) + ", erhalten " + print(actual));
    }
}

void registerEndterm2023(Registry& registry);
void registerEndterm2024(Registry& registry);
void registerEndterm2025(Registry& registry);
void registerRetake2023(Registry& registry);
void registerRetake2024(Registry& registry);
void registerRetake2025(Registry& registry);

}
