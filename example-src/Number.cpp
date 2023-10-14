#include "Number.h"

bool DecimalNumber::isItEquivalent(std::string str)
{
    double num;
    try
    {
        num = std::stof(str);
    }
    catch (...)
    {
        return false;
    }
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
