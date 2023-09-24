#include "QuestionGenerator.h"
#include "Number.h"
#include "HexNumber.h"
#include "BinaryNumber.h"

enum Types
{
	BINARY,
	DECIMAL,
	HEX,
	TYPES_COUNT,
};

const int MAX_NUM = 0xF;

ItemPtr QuestionGenerator::getQuestion()
{
	return m_question;
}

ItemPtr QuestionGenerator::getAnswer()
{
	return m_answer;
}

void QuestionGenerator::generate()
{
	int ans = m_rng->getRandomNum() % TYPES_COUNT;
	int question = ans;
	// get a unique question
	while (question == ans)
	{
		question = m_rng->getRandomNum() % TYPES_COUNT;
	}
	// get a number between 0 and 15
	int num = m_rng->getRandomNum() % (MAX_NUM + 1);
	// get a suitable answer
	if ((((ans == HEX) && (question == DECIMAL)) ||
		((ans == DECIMAL) && (question == HEX))) &&
		(num < 0xA))
	{
		// between 10 and 15
		num %= 6;
		num += 10;
	}
	m_answer = generate(ans, num);
	m_question = generate(question, num);
}

ItemPtr QuestionGenerator::generate(int item, int num)
{
	ItemPtr ret;
	switch (item)
	{
	case BINARY:
		ret = std::make_shared<BinaryNumber>(num);
		break;
	case DECIMAL:
		ret = std::make_shared<DecimalNumber>(num);
		break;
	case HEX:
		ret = std::make_shared<HexNumber>(num);
		break;
	default:
		break;
	}
	return ret;
}
