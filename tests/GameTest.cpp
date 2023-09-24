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
    std::queue<std::pair<ItemPtr, ItemPtr>> items;
    void generate() override
    {
        std::pair<ItemPtr, ItemPtr> item = items.front();
        items.pop();
        m_question = item.first;
        m_answer = item.second;
    }
    ItemPtr getQuestion()
    {
        return m_question;
    }
    ItemPtr getAnswer()
    {
        return m_answer;
    }
    ItemPtr m_answer;
    ItemPtr m_question;
};

TEST(GameTest, game_test)
{
    // given
    // make the questions
    std::shared_ptr<DecimalNumber> question = std::make_shared<DecimalNumber>(10);
    std::shared_ptr<HexNumber> answer = std::make_shared <HexNumber>(10);
    TestableNumberGenerator testable_generator;
    testable_generator.items.push(
        std::make_pair<ItemPtr, ItemPtr>(question, answer));
    // prepare the console
    std::stringstream input_ss("0xa");
    std::stringstream output_ss;
    // when
    // run the game
    Game game(&input_ss, &output_ss, &testable_generator);
    game.tick();
    // then
    CHECK_EQUAL("What is 10 decimal in hex?\nCorrect!\n", output_ss.str());
}

TEST(GameTest, game_score_can_be_ascertained)
{
    // given
    // make the questions
    std::shared_ptr<DecimalNumber> question = std::make_shared<DecimalNumber>(10);
    std::shared_ptr<HexNumber> answer = std::make_shared <HexNumber>(10);
    TestableNumberGenerator testable_generator;
    testable_generator.items.push(
        std::make_pair<ItemPtr, ItemPtr>(question, answer));
    testable_generator.items.push(
        std::make_pair<ItemPtr, ItemPtr>(question, answer));
    testable_generator.items.push(
        std::make_pair<ItemPtr, ItemPtr>(question, answer));
    // prepare the console
    std::stringstream input_ss("0xa 0xb 0xb");
    std::stringstream output_ss;
    Game game(&input_ss, &output_ss, &testable_generator);
    CHECK_EQUAL(0, game.correctAnswers());
    CHECK_EQUAL(0, game.wrongAnswers());
    // when
    // run the game
    game.tick();
    game.tick();
    game.tick();
    // then
    CHECK_EQUAL(1, game.correctAnswers());
    CHECK_EQUAL(2, game.wrongAnswers());
}