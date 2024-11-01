cmake_minimum_required(VERSION 3.10)
project(four)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем директории с заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR}/include)

# Создаем библиотеку из исходных файлов
add_library(four_lib
    src/four.cpp
)

# Добавляем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# Тесты
add_executable(four_test
    tests/four_test.cpp
)

target_link_libraries(four_test
    PRIVATE
    four_lib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(four_test)
