#include "CppUTest/TestHarness.h"
#include "BinaryNumber.h"
#include <memory>

extern "C"
{
    /*
     * You can add your c-only include files here
     */
}

TEST_GROUP(BinaryNumberTest)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(BinaryNumberTest, equivalency_tests)
{
    CHECK_EQUAL(true, BinaryNumber(1).isItEquivalent("1"));
    CHECK_EQUAL(true, BinaryNumber(5).isItEquivalent("101"));
    CHECK_EQUAL(true, BinaryNumber(5).isItEquivalent("00101"));
}

TEST(BinaryNumberTest, false_tests)
{
    CHECK_EQUAL(false, BinaryNumber(1).isItEquivalent("11"));
}

TEST(BinaryNumberTest, get_string_shows_binary_representation)
{
    CHECK_EQUAL("1001", BinaryNumber(9).getString());
}

TEST(BinaryNumberTest, get_type)
{
    CHECK_EQUAL("binary", BinaryNumber(9).getBaseString());
}

TEST(BinaryNumberTest, handles_bad_input_gracefully)
{
    BinaryNumber number(7);
    CHECK_EQUAL(false, number.isItEquivalent("2"));
}
