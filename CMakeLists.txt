cmake_minimum_required(VERSION 3.20)

project(AuD_Klausurtraining LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(add_exam_module target)
    add_library(${target} STATIC ${ARGN})
    target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_compile_options(${target} PRIVATE
        $<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall >
    )
endfunction()

add_exam_module(endterm_2023
    endterm-2023/endterm-2023-exercise-09.cpp
    endterm-2023/endterm-2023-exercise-10.cpp
)

add_exam_module(endterm_2024
    endterm-2024/endterm-2024-exercise-01.cpp
    endterm-2024/endterm-2024-exercise-05.cpp
    endterm-2024/endterm-2024-exercise-06.cpp
    endterm-2024/endterm-2024-exercise-09.cpp
    endterm-2024/endterm-2024-exercise-10.cpp
)

add_exam_module(endterm_2025
    endterm-2025/endterm-2025-exercise-06.cpp
    endterm-2025/endterm-2025-exercise-07.cpp
    endterm-2025/endterm-2025-exercise-10.cpp
)

add_exam_module(retake_2023
    retake-2023/retake-2023-exercise-09.cpp
    retake-2023/retake-2023-exercise-10.cpp
)

add_exam_module(retake_2024
    retake-2024/retake-2024-exercise-01.cpp
    retake-2024/retake-2024-exercise-05.cpp
    retake-2024/retake-2024-exercise-09.cpp
    retake-2024/retake-2024-exercise-10.cpp
)

add_exam_module(retake_2025
    retake-2025/retake-2025-exercise-06.cpp
    retake-2025/retake-2025-exercise-07.cpp
    retake-2025/retake-2025-exercise-10.cpp
)

add_executable(Testsuite
    tests/main.cpp
    tests/endterm-2023-tests.cpp
    tests/endterm-2024-tests.cpp
    tests/endterm-2025-tests.cpp
    tests/retake-2023-tests.cpp
    tests/retake-2024-tests.cpp
    tests/retake-2025-tests.cpp
)

target_include_directories(Testsuite PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests"
)
target_link_libraries(Testsuite PRIVATE
    endterm_2023
    endterm_2024
    endterm_2025
    retake_2023
    retake_2024
    retake_2025
)

enable_testing()
add_test(NAME all-exams COMMAND Testsuite)
foreach(exam IN ITEMS
        endterm-2023 endterm-2024 endterm-2025
        retake-2023 retake-2024 retake-2025)
    add_test(NAME "${exam}" COMMAND Testsuite "${exam}")
endforeach()
