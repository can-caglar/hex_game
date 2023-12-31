#include "CppUTest/TestHarness.h"
#include "Number.h"
#include "HexNumber.h"
#include "Questioner.h"

extern "C"
{
    /*
     * You can add your c-only include files here
     */
}

TEST_GROUP(QuestionerTests)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(QuestionerTests, decimal_to_decimal_question)
{
    
    Questioner questioner;
    std::shared_ptr<DecimalNumber> question= std::make_shared<DecimalNumber>(10);
    std::shared_ptr<DecimalNumber> answer = std::make_shared<DecimalNumber>(10);
    
    std::string question_string = questioner.generateQuestion(question, answer);

    CHECK_EQUAL("What is 10 decimal in decimal?\n", question_string);
}

TEST(QuestionerTests, decimal_to_hexadecimal_question)
{
    std::shared_ptr<DecimalNumber> question = std::make_shared<DecimalNumber>(10);
    std::shared_ptr<HexNumber> answer = std::make_shared<HexNumber>(10);

    Questioner questioner;

    std::string question_string = questioner.generateQuestion(question, answer);

    CHECK_EQUAL("What is 10 decimal in hex?\n", question_string);
}

TEST(QuestionerTests, hexadecimal_to_decimal_question)
{
    std::shared_ptr<DecimalNumber> answer = std::make_shared<DecimalNumber>(10);
    std::shared_ptr<HexNumber> question = std::make_shared<HexNumber>(10);

    Questioner questioner;

    std::string question_string = questioner.generateQuestion(question, answer);

    CHECK_EQUAL("What is 0xA hex in decimal?\n", question_string);
}

TEST(QuestionerTests, generate_response_correct_answer)
{
    std::shared_ptr<HexNumber> question = std::make_shared<HexNumber>(10);
    std::shared_ptr<DecimalNumber> answer = std::make_shared<DecimalNumber>(10);

    Questioner questioner;
    std::string question_string = questioner.generateQuestion(question, answer);

    std::string ans("10");
    CHECK_EQUAL("Correct!\n", questioner.generateResponseTo(ans));
}


TEST(QuestionerTests, generate_response_wrong_answer)
{
    std::shared_ptr<HexNumber> question= std::make_shared<HexNumber>(10);
    std::shared_ptr<DecimalNumber> answer = std::make_shared<DecimalNumber>(10);

    Questioner questioner;
    std::string question_string = questioner.generateQuestion(question, answer);

    std::string ans("9");
    CHECK_EQUAL("Wrong! 0xA in decimal is 10.\n", questioner.generateResponseTo(ans));
}
