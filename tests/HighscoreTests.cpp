#include "CppUTest/TestHarness.h"
#include "Highscores.h"
#include <sstream>

class MyDataStorage : public IDataStorage
{
public:
    MyDataStorage(std::ostringstream& oss, std::istringstream& iss) : m_oss(oss), m_iss(iss)
    {
    };
    void writeLine(std::string line)
    {
        m_oss << line;
    }
    std::string readLine()
    {
        std::string str;
        std::getline(m_iss, str);
        return str;
    }
protected:
    std::ostringstream& m_oss;
    std::istringstream& m_iss;
};

TEST_GROUP(HighScoreTest)
{
    std::ostringstream oss;
    std::istringstream iss;
    IDataStoragePtr ds;
    void setup()
    {
        ds = std::make_shared<MyDataStorage>(oss, iss);
    }
    void teardown()
    {
    }
};

bool areEqual(const HighscoreEntry& lhs, const HighscoreEntry& rhs)
{
    return (lhs.name == rhs.name) &&
        (lhs.score == rhs.score) &&
        (lhs.timestamp == lhs.timestamp);
}

TEST(HighScoreTest, NewlyAddedEntryUpdatesSizeAndCanBeRetrievedAndIsSavedToDisk)
{
    HighscoreEntry entry{ "Can", 578, "123" };
    Highscores highscores(ds);

    highscores.add(entry);
    highscores.save();

    CHECK_EQUAL(1, highscores.size());
    CHECK(areEqual(entry, highscores.get(0)));
    CHECK_EQUAL("Can 578 123", oss.str());
}

TEST(HighScoreTest, HighscoresOnDiskAreRetrieved)
{
    iss.str("Can 578 123");
    HighscoreEntry expectedEntry{ "Can", 578, "123" };
    
    Highscores highscores(ds);

    CHECK_EQUAL(1, highscores.size());
    CHECK(areEqual(expectedEntry, highscores.get(0)));
}

TEST(HighScoreTest, MultipleHighScoresAreSavedAndReceivedInOrderOfPoints)
{
    HighscoreEntry entry{ "Can", 578, "123" };
    HighscoreEntry entryWithHigherScore{ "Caglar", 999, "078" };
    Highscores highscores(ds);

    highscores.add(entry);
    highscores.add(entryWithHigherScore);

    highscores.save();

    CHECK_EQUAL(2, highscores.size());
    CHECK(areEqual(entryWithHigherScore, highscores.get(0)));
    CHECK(areEqual(entry, highscores.get(1)));
}

/*
Tests:

- Highscores are retrieved from a stream
- New highscores are saved to stream
- Highscores are saved encrypted
- Highscores are read properly from an encrypted source
- Number of entries on the highscores can be ascertained
- All highscores can be retrieved
*/