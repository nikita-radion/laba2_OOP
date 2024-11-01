#include <gtest/gtest.h>
#include "four.h"
#include <iostream>

inline Four F(const char* str) {
    return Four(str);
}

TEST(FourTest, DefaultConstructor) {
    Four f;
    EXPECT_EQ(f.size(), 1);
    EXPECT_EQ(f.get(0), '0');
}

TEST(FourTest, StringConstructor) {
    Four f = F("123");
    EXPECT_EQ(f.size(), 3);
    EXPECT_EQ(f.get(0), '1');
    EXPECT_EQ(f.get(1), '2');
    EXPECT_EQ(f.get(2), '3');
}

TEST(FourTest, CopyConstructor) {
    Four f1 = F("123");
    Four f2(f1);
    EXPECT_EQ(f1.size(), f2.size());
    for (size_t i = 0; i < f1.size(); ++i) {
        EXPECT_EQ(f1.get(i), f2.get(i));
    }
}

TEST(FourTest, MoveConstructor) {
    Four f1 = F("123");
    Four f2(std::move(f1));
    EXPECT_EQ(f2.size(), 3);
    EXPECT_EQ(f2.get(0), '1');
    EXPECT_EQ(f2.get(1), '2');
    EXPECT_EQ(f2.get(2), '3');
    EXPECT_EQ(f1.size(), 0);
}

TEST(FourTest, Addition) {
    Four f1 = F("12");
    Four f2 = F("23");
    Four result = f1 + f2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result.get(0), '1');
    EXPECT_EQ(result.get(1), '0');
    EXPECT_EQ(result.get(2), '1');
}

TEST(FourTest, Subtraction) {
    Four f1 = F("23");
    Four f2 = F("12");
    Four result = f1 - f2;
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.get(0), '1');
    EXPECT_EQ(result.get(1), '1');
}

TEST(FourTest, AdditionAssignment) {
    Four f1 = F("12");
    Four f2 = F("23");
    f1 += f2;
    EXPECT_EQ(f1.size(), 3);
    EXPECT_EQ(f1.get(0), '1');
    EXPECT_EQ(f1.get(1), '0');
    EXPECT_EQ(f1.get(2), '1');
}

TEST(FourTest, SubtractionAssignment) {
    Four f1 = F("23");
    Four f2 = F("12");
    f1 -= f2;
    EXPECT_EQ(f1.size(), 2);
    EXPECT_EQ(f1.get(0), '1');
    EXPECT_EQ(f1.get(1), '1');
}

TEST(FourTest, GreaterThan) {
    Four f1 = F("23");
    Four f2 = F("12");
    EXPECT_TRUE(f1 > f2);
    EXPECT_FALSE(f2 > f1);
}

TEST(FourTest, LessThan) {
    Four f1 = F("12");
    Four f2 = F("23");
    EXPECT_TRUE(f1 < f2);
    EXPECT_FALSE(f2 < f1);
}

TEST(FourTest, EqualTo) {
    Four f1 = F("23");
    Four f2 = F("23");
    Four f3 = F("12");
    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 == f3);
}

TEST(FourTest, SetAndGet) {
    Four f = F("000");
    f.set(1, '2');
    EXPECT_EQ(f.get(1), '2');
    EXPECT_EQ(f.get(0), '0');
    EXPECT_THROW(f.get(3), std::out_of_range);
    EXPECT_THROW(f.set(3, '2'), std::out_of_range);
    EXPECT_THROW(f.set(1, '4'), std::invalid_argument);
}

TEST(FourTest, InvalidInput) {
    EXPECT_THROW(F("124"), std::invalid_argument);
    EXPECT_THROW(F("abc"), std::invalid_argument);
}

TEST(FourTest, SubtractionWithNegativeResult) {
    Four f1 = F("12");
    Four f2 = F("23");
    EXPECT_THROW(f1 - f2, std::runtime_error);
}

TEST(FourTest, AdditionWithCarry) {
    Four f1 = F("33");
    Four f2 = F("01");
    Four result = f1 + f2;
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result.get(0), '1');
    EXPECT_EQ(result.get(1), '0');
    EXPECT_EQ(result.get(2), '0');
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

