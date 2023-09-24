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
        "?";

    return ret;
}

std::string Questioner::generateResponseTo(std::string ansStr)
{
    if (m_Ans->isItEquivalent(ansStr))
    {
        return "Correct!";
    }
    else
    {
        return "Wrong! " +
            m_Question->getString() +
            " in " +
            m_Ans->getBaseString() +
            " is " +
            m_Ans->getString() +
            ".";
    }
}
