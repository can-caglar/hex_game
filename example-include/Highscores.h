#pragma once

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <set>

class IDataStorage
{
public:
    virtual void writeLine(std::string line) = 0;
    virtual std::string readLine() = 0;
};

struct HighscoreEntry
{
    std::string name;
    uint32_t score;
    std::string timestamp;
    bool operator>(const HighscoreEntry& other) const
    {
        return score > other.score;
    }
};

typedef std::shared_ptr<IDataStorage> IDataStoragePtr;

class Highscores
{
public:
    Highscores(IDataStoragePtr ds) : m_dataStorage(ds)
    {
        HighscoreEntry newEntry;
        std::istringstream iss;
        iss.str(ds->readLine());
        if (iss.str().size() > 0)
        {
            std::string str;
            iss >> str; // name
            newEntry.name = str;
            iss.get();  // ignore space
            iss >> str;
            newEntry.score = std::atol(str.c_str());
            iss.get();  //ignore space
            iss >> str;
            newEntry.timestamp = str;
            m_highscores.insert(newEntry);
        }
    };
    void add(const HighscoreEntry& entry);
    uint32_t size();
    const HighscoreEntry& get(uint32_t index);
    void save();
protected:
    IDataStoragePtr m_dataStorage;
    //std::vector<HighscoreEntry> m_highscores;
    std::multiset<HighscoreEntry, std::greater<HighscoreEntry>> m_highscores;
};
