#include "CppUTest/TestHarness.h"
#include "QuestionGenerator.h"
#include <queue>

extern "C"
{
    /*
     * You can add your c-only include files here
     */
}

class TestableRNG : public IRNG
{
public:
    TestableRNG() : m_nums(), m_finalNum{ 0 } {};
    void toReturn(int num) { m_nums.push(num); }
    int getRandomNum() override
    {
        if (m_nums.empty())
        {
            return m_finalNum;
        }
        int n = m_nums.front();
        m_nums.pop();
        if (m_nums.empty())
        {
            m_finalNum = n;
        }
        return n;
    }
private:
    std::queue<int> m_nums;
    int m_finalNum;
};

TEST_GROUP(QuestionGeneratorTests)
{
    std::shared_ptr<TestableRNG> testRNG;
    void setup()
    {
        testRNG = std::make_shared<TestableRNG>();
    }

    void teardown()
    {
    }
};

TEST(QuestionGeneratorTests, RNGTest)
{
    CHECK_EQUAL(0, testRNG->getRandomNum());
    testRNG->toReturn(7);
    CHECK_EQUAL(7, testRNG->getRandomNum());
    CHECK_EQUAL(7, testRNG->getRandomNum());
    testRNG->toReturn(-1);
    CHECK_EQUAL(-1, testRNG->getRandomNum());

    testRNG->toReturn(9);
    testRNG->toReturn(8);
    testRNG->toReturn(7);
    CHECK_EQUAL(9, testRNG->getRandomNum());
    CHECK_EQUAL(8, testRNG->getRandomNum());
    CHECK_EQUAL(7, testRNG->getRandomNum());
}

enum Types
{
    BINARY,
    DECIMAL,
    HEX,
    TYPES_COUNT,
};

TEST(QuestionGeneratorTests, rng_returns_answer_then_question_then_number)
{
    testRNG->toReturn(DECIMAL);     // answer decimal
    testRNG->toReturn(HEX);         // question hex
    testRNG->toReturn(10);          // value Should be 10
    QuestionGenerator g(testRNG);

    g.generate();

    ItemPtr answer = g.getAnswer();
    ItemPtr question = g.getQuestion();
    CHECK_EQUAL("decimal", answer->getBaseString());
    CHECK_EQUAL("10", answer->getString());
    CHECK_EQUAL("hex", question->getBaseString());
    CHECK_EQUAL("0xA", question->getString());
}


TEST(QuestionGeneratorTests, rng_value_larger_will_get_modulo_applied)
{
    testRNG->toReturn(TYPES_COUNT + HEX);       // answer hex
    testRNG->toReturn(TYPES_COUNT + DECIMAL);   // question decimal
    testRNG->toReturn(31);                      // max is 0xF, expect % 16
    QuestionGenerator g(testRNG);

    g.generate();

    ItemPtr answer = g.getAnswer();
    ItemPtr question = g.getQuestion();

    CHECK_EQUAL("hex", answer->getBaseString());
    CHECK_EQUAL("0xF", answer->getString());
    CHECK_EQUAL("decimal", question->getBaseString());
    CHECK_EQUAL("15", question->getString());
}

TEST(QuestionGeneratorTests, if_its_between_hex_and_dec_num_must_be_greater_than_9)
{
    testRNG->toReturn(HEX);       // answer hex
    testRNG->toReturn(DECIMAL);   // question decimal
    testRNG->toReturn(6);         // less than 10. This'll be converted
                                  // to being between 10 - 15 (6%6 + 10)
    QuestionGenerator g(testRNG);

    g.generate();

    ItemPtr answer = g.getAnswer();
    ItemPtr question = g.getQuestion();

    CHECK_EQUAL("hex", answer->getBaseString());
    CHECK_EQUAL("0xA", answer->getString());
    CHECK_EQUAL("decimal", question->getBaseString());
    CHECK_EQUAL("10", question->getString());
}

TEST(QuestionGeneratorTests, rng_returns_same_number_for_types)
{
    testRNG->toReturn(HEX);       // answer hex
    testRNG->toReturn(HEX);       // roll again 
    testRNG->toReturn(HEX);       // ...
    testRNG->toReturn(DECIMAL);   // until not the same
    testRNG->toReturn(13);

    QuestionGenerator g(testRNG);
    g.generate();

    ItemPtr answer = g.getAnswer();
    ItemPtr question = g.getQuestion();

    CHECK_EQUAL("hex", answer->getBaseString());
    CHECK_EQUAL("0xD", answer->getString());
    CHECK_EQUAL("decimal", question->getBaseString());
    CHECK_EQUAL("13", question->getString());
}


IGNORE_TEST(QuestionGeneratorTests, to_test_binary)
{
    // to test returning binary
}
