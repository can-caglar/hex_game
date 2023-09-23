#include "INumberGenerator.h"
#include <memory>

class IRNG
{
public:
	virtual int getRandomNum() = 0;
};

typedef std::shared_ptr<IRNG> RNGPtr;

class QuestionGenerator : public INumberGenerator
{
public:
	QuestionGenerator(RNGPtr rng) : m_rng{ rng },
		m_question{ nullptr },
		m_answer{ nullptr } 
	{};
	ItemPtr getQuestion() override;
	ItemPtr getAnswer() override;
	void generate() override;
private:
	ItemPtr generate(int item, int num);

	RNGPtr m_rng;
	ItemPtr m_question;
	ItemPtr m_answer;
};
