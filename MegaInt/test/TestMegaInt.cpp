#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "MegaInt.h"

TEST_CASE("Public Methods")
{
    MegaInt blank = MegaInt();

    char const signPositive = '+';
    auto zeroDeque = std::deque<char>();
    zeroDeque.push_front('0');
    MegaInt zero = MegaInt(signPositive, zeroDeque);

    CHECK(blank.GetSign() == signPositive);
    CHECK(blank.GetMagnitude() == zeroDeque);
    CHECK(blank == zero);

    MegaInt explicitCtor = MegaInt("0");
    CHECK(explicitCtor == zero);

    MegaInt minusTwentyTwo = MegaInt("-22");
    minusTwentyTwo.Negate();
    CHECK(minusTwentyTwo.GetSign() == signPositive);
    minusTwentyTwo.Clear();
    CHECK(minusTwentyTwo.GetMagnitude() == zeroDeque);
}

TEST_CASE("Mathematical Operators")
{
    MegaInt minustwo = MegaInt("-2");
    MegaInt zero = MegaInt();
    MegaInt two = MegaInt("2");
    MegaInt three = MegaInt("3");
    MegaInt four = MegaInt("4");

    auto temp = zero + two;
    CHECK(temp == two);

    temp = temp * two;
    CHECK(temp == four);

    temp = temp - four;
    CHECK(temp == zero);

    temp = temp + four;
    temp = temp / two;
    CHECK(temp == two);

    temp++;
    CHECK(temp == three);

    temp -= temp;
    CHECK(temp == zero);

    temp += temp;
    CHECK(temp == zero);

    temp -= two;
    CHECK(temp == minustwo);

    CHECK(two < four);
    CHECK(four >= three);
    CHECK(two != minustwo);
}
