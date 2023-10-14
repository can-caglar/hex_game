#include "CppUTest/TestHarness.h"
#include "Highscores.h"
#include "MyEncryptor.h"
#include <sstream>

class MyDataStorage : public IDataStorage
{
public:
    MyDataStorage(std::ostringstream& oss, std::istringstream& iss) : m_oss(oss), m_iss(iss)
    {
    };
    void writeLine(std::string line) override
    {
        m_oss << line;
    }
    std::string readLine() override
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
    IEncryptorPtr encryptor;
    void setup()
    {
        ds = std::make_shared<MyDataStorage>(oss, iss);
        encryptor = std::make_shared<MyEncryptor>();
    }
    void teardown()
    {
    }
};

bool areEqual(const HighscoreEntry& lhs, const HighscoreEntry& rhs)
{
    CHECK_EQUAL(lhs.name, rhs.name);
    CHECK_EQUAL(lhs.score, rhs.score);
    CHECK_EQUAL(lhs.timestamp, rhs.timestamp);
    
    return true;
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

TEST(HighScoreTest, MultipleHighScoresAreSavedThenReceivedInOrderOfPoints)
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


TEST(HighScoreTest, HighScoresCanBeEncrypted)
{
    HighscoreEntry entry{ "Can", 578, "123" };
    Highscores highscores(ds, encryptor);

    highscores.add(entry);
    highscores.save();

    CHECK_EQUAL(oss.str(), encryptor->encrypt("Can 578 123"));
}

TEST(HighScoreTest, EncryptedHighScoresCanBeDecrypted)
{
    std::string str = encryptor->encrypt("Can 578 123");
    iss.str(str);
    HighscoreEntry expectedEntry = { "Can", 578, "123" };

    Highscores highscores(ds, encryptor);
    highscores.save();

    CHECK(areEqual(expectedEntry, highscores.get(0)));
    CHECK_EQUAL(oss.str(), encryptor->encrypt("Can 578 123"));
}

TEST(HighScoreTest, MultipleHighscoresAreRetrievedFromDisk)
{
    std::ostringstream outstr;
    outstr << "Can 578 123\n";
    outstr << "Caglar 999 012\n";
    iss.str(outstr.str());

    HighscoreEntry expectedEntry = { "Can", 578, "123" };
    HighscoreEntry expectedEntry2 = { "Caglar", 999, "012" };

    Highscores highscores(ds);

    CHECK_EQUAL(2, highscores.size());
    CHECK(areEqual(expectedEntry2, highscores.get(0)));
    CHECK(areEqual(expectedEntry, highscores.get(1)));
}

TEST(HighScoreTest, MultipleHighscoresAreRetrievedFromDiskEvenIfEncrypted)
{
    std::ostringstream outstr;
    outstr << "Can 578 123\n";
    outstr << "Caglar 999 012\n";
    iss.str(encryptor->encrypt(outstr.str()));

    HighscoreEntry expectedEntry = { "Can", 578, "123" };
    HighscoreEntry expectedEntry2 = { "Caglar", 999, "012" };

    Highscores highscores(ds, encryptor);

    CHECK_EQUAL(2, highscores.size());
    CHECK(areEqual(expectedEntry2, highscores.get(0)));
    CHECK(areEqual(expectedEntry, highscores.get(1)));
}


TEST(HighScoreTest, SizeDoesNotGoAboveCertainValue)
{
    Highscores highscores(ds, encryptor);
    for (uint8_t i = 0; i < 20; i++)
    {
        HighscoreEntry entry{ "Can", i, "123" };
        highscores.add(entry);
    }

    highscores.save();

    CHECK_EQUAL(12, highscores.size());
}

IGNORE_TEST(HighScoreTest, retrievingMoreThanMaxOrMoreThanAvailableIsHandledGracefully)
{
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