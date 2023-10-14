#pragma once
#include "Highscores.h"

class MyEncryptor : public IEncryptor
{
public:
    std::string encrypt(std::string line) override;
    std::string decrypt(std::string line) override;
};