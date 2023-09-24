#include "BinaryNumber.h"
#include <bitset>

bool BinaryNumber::isItEquivalent(std::string val)
{
	std::bitset<32> bitset(val);
	int num = static_cast<int>(bitset.to_ulong());
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
