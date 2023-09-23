#include "CppUTest/TestHarness.h"
#include <memory>

#include "Number.h"

extern "C"
{
	/*
	 * You can add your c-only include files here
	 */
}

TEST_GROUP(DecimalNumberTest)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(DecimalNumberTest, decimal_number_is_correct_when_correct_value_passed_in)
{
    DecimalNumber number(7);
    // true
    CHECK_TRUE(number.isItEquivalent("7"));
    CHECK_TRUE(number.isItEquivalent("00007"));
    CHECK_TRUE(number.isItEquivalent("7.0"));

    // false
    CHECK_FALSE(number.isItEquivalent("6"));
    CHECK_FALSE(number.isItEquivalent("7.1"));
    CHECK_FALSE(number.isItEquivalent("7.000001"));
}

TEST(DecimalNumberTest, decimal_number_name)
{
    DecimalNumber number(7);
    CHECK_EQUAL("7", number.getString());
}

TEST(DecimalNumberTest, decimal_number_base)
{
    DecimalNumber number(7);
    CHECK_EQUAL("decimal", number.getBaseString());
}

