#include "Number.h"

bool DecimalNumber::isItEquivalent(std::string str)
{
    double num = std::stof(str);
    return num == m_num;
}

std::string DecimalNumber::getString()
{
    return std::to_string((int)m_num);
}

std::string DecimalNumber::getBaseString()
{
    return "decimal";
}
