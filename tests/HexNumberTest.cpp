#include "CppUTest/TestHarness.h"
#include <memory>

#include "HexNumber.h"

extern "C"
{
    /*
     * You can add your c-only include files here
     */
}

TEST_GROUP(HexNumberTest)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(HexNumberTest, number_less_than_10_equivalency_tests)
{
    HexNumber hex(3);
    // true
    CHECK_TRUE(hex.isItEquivalent("3"));
    CHECK_TRUE(hex.isItEquivalent("0x3"));
    CHECK_TRUE(hex.isItEquivalent("0x00003"));

    // false
    CHECK_FALSE(hex.isItEquivalent("4"));
}

TEST(HexNumberTest, number_more_than_10_equivalency_tests)
{
    HexNumber hex(13);
    // true
    CHECK_TRUE(hex.isItEquivalent("0xD"));
    CHECK_TRUE(hex.isItEquivalent("0xd"));

    // false
    CHECK_FALSE(hex.isItEquivalent("13"));
}

TEST(HexNumberTest, number_string_has_0x_in_front_and_is_capitalised)
{
    HexNumber hex13(13);
    HexNumber hex2(2);
    CHECK_EQUAL("0xD", hex13.getString());
    CHECK_EQUAL("0x2", hex2.getString());
}
