#include "BinaryNumber.h"
#include <bitset>

bool BinaryNumber::isItEquivalent(std::string val)
{
	int num;
	try
	{
		std::bitset<32> bitset(val);
		num = static_cast<int>(bitset.to_ulong());
	}
	catch (...)
	{
		return false;
	}
	return num == m_num;
}
std::string BinaryNumber::getString()
{
	std::bitset<4> bitset(m_num);
	return bitset.to_string();
}
std::string BinaryNumber::getBaseString()
{
	return "binary";
}
