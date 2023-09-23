#include "HexNumber.h"
#include <sstream>

bool HexNumber::isItEquivalent(std::string val)
{
	int a = std::stoi(val, nullptr, 16);
	return a == m_num;
}

std::string HexNumber::getString()
{
	std::stringstream ss;
	ss << std::hex << std::uppercase << m_num;
	return "0x" + ss.str();
}

std::string HexNumber::getBaseString()
{
	return num_id_hex;
}
