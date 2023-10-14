#include "MyEncryptor.h"

std::string MyEncryptor::encrypt(std::string line)
{
    for (auto& c : line)
    {
        if (c != '\n')
        {
            c ^= 'K';
        }
    }
    return line;
}

std::string MyEncryptor::decrypt(std::string line)
{
    return encrypt(line);
}
