#include "QuestionGenerator.h"
#include "Number.h"
#include "HexNumber.h"

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
	int question = m_rng->getRandomNum() % TYPES_COUNT;
	int num = m_rng->getRandomNum() % (MAX_NUM + 1);

	m_answer = generate(ans, num);
	m_question = generate(question, num);
}

ItemPtr QuestionGenerator::generate(int item, int num)
{
	ItemPtr ret;
	switch (item)
	{
	case BINARY:
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
