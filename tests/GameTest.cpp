#include "CppUTest/TestHarness.h"
#include "IItem.h"
#include <sstream>
#include <queue>
#include "INumberGenerator.h"
#include "HexNumber.h"
#include "Number.h"
#include "Game.h"

extern "C"
{
    /*
     * You can add your c-only include files here
     */
}

TEST_GROUP(GameTest)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

class TestableNumberGenerator : public INumberGenerator
{
public:
    TestableNumberGenerator() : items(), m_question(), m_answer() {};
    std::queue<std::pair<IItem*, IItem*>> items;
    IItem* m_question;
    IItem* m_answer;
    void generate() override
    {
        std::pair<IItem*, IItem*> item = items.front();
        items.pop();
        m_question = item.first;
        m_answer = item.second;
    }
};

IGNORE_TEST(GameTest, game_test)
{
    // given
    DecimalNumber question(10);
    HexNumber answer(10);
    TestableNumberGenerator testable_generator;
    testable_generator.items.push(
        std::make_pair<IItem*, IItem*>(&question, &answer));
    std::stringstream input_ss("0xa");
    std::stringstream output_ss;
    // when
    Game game(&input_ss, &output_ss, &testable_generator);
    game.tick();
    // then
    CHECK_EQUAL("What is 10 decimal in hex? Correct!", output_ss.str());
}
