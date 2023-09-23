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
    DecimalNumber question(10);
    DecimalNumber answer(10);
    
    std::string question_string = questioner.generateQuestion(&question, &answer);

    CHECK_EQUAL("What is 10 decimal in decimal?", question_string);
}

TEST(QuestionerTests, decimal_to_hexadecimal_question)
{
    DecimalNumber question(10);
    HexNumber answer(10);

    Questioner questioner;

    std::string question_string = questioner.generateQuestion(&question, &answer);

    CHECK_EQUAL("What is 10 decimal in hex?", question_string);
}

TEST(QuestionerTests, hexadecimal_to_decimal_question)
{
    HexNumber question(10);
    DecimalNumber answer(10);

    Questioner questioner;

    std::string question_string = questioner.generateQuestion(&question, &answer);

    CHECK_EQUAL("What is 0xA hex in decimal?", question_string);
}

TEST(QuestionerTests, generate_response_correct_answer)
{
    HexNumber question(10);
    DecimalNumber answer(10);

    Questioner questioner;
    std::string question_string = questioner.generateQuestion(&question, &answer);


    std::string ans("10");
    CHECK_EQUAL("Correct!", questioner.generateResponseTo(ans));
}


TEST(QuestionerTests, generate_response_wrong_answer)
{
    HexNumber question(10);
    DecimalNumber answer(10);

    Questioner questioner;
    std::string question_string = questioner.generateQuestion(&question, &answer);

    std::string ans("9");
    CHECK_EQUAL("Wrong! 0xA in decimal is 10.", questioner.generateResponseTo(ans));
}
