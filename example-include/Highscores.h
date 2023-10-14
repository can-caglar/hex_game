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

class IEncryptor
{
public:
    virtual std::string encrypt(std::string line) = 0;
    virtual std::string decrypt(std::string line) = 0;
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
typedef std::shared_ptr<IEncryptor> IEncryptorPtr;

class Highscores
{
public:
    Highscores(IDataStoragePtr ds, IEncryptorPtr encryptor = nullptr) : m_dataStorage(ds), m_encryptor(encryptor)
    {
        HighscoreEntry newEntry;
        std::string line;
        while ((line = ds->readLine()) != "")
        {
            if (m_encryptor)
            {
                line = m_encryptor->decrypt(line);
            }
            std::istringstream iss(line);
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
        }
    };
    void add(const HighscoreEntry& entry);
    uint32_t size();
    const HighscoreEntry& get(uint32_t index);
    void save();
protected:
    IDataStoragePtr m_dataStorage;
    IEncryptorPtr m_encryptor;
    std::multiset<HighscoreEntry, std::greater<HighscoreEntry>> m_highscores;
    static const uint32_t maxScore;
};
