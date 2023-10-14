#pragma once

#include "Highscores.h"
#include <fstream>
#include <sstream>

class FileStorage : public IDataStorage
{
public:
    FileStorage(std::string filename) : m_filename(filename)
    {
        // Store the file internally
        std::ifstream ifs(filename);
        std::string str;
        while (std::getline(ifs, str))
        {
            oss << str + '\n';
        }
        iss.str(oss.str());
        ifs.close();
    };
    ~FileStorage()
    {
        // Save to file
        std::ofstream ofs(m_filename);
        ofs << oss.str();
    }
    void writeLine(std::string line) override
    {
        oss << line << '\n';
    }
    std::string readLine() override
    {
        std::string str;
        if (!std::getline(iss, str))
        {
            str = "";
        }
        return str;
    }
protected:
    std::string m_filename;
    std::istringstream iss;
    std::ostringstream oss;
};