#include "Questioner.h"

std::string Questioner::generateQuestion(ItemPtr q, ItemPtr a)
{
    m_Question = q;
    m_Ans = a;
    std::string ret = "What is ";
    ret += q->getString() +
        " " +
        q->getBaseString() +
        " in " + a->getBaseString() +
        "?\n";

    return ret;
}

std::string Questioner::generateResponseTo(std::string ansStr)
{
    if (m_Ans->isItEquivalent(ansStr))
    {
        ++m_correctAnswers;
        return "Correct!\n";
    }
    else
    {
        ++m_wrongAnswers;
        return "Wrong! " +
            m_Question->getString() +
            " in " +
            m_Ans->getBaseString() +
            " is " +
            m_Ans->getString() +
            ".\n";
    }
}
