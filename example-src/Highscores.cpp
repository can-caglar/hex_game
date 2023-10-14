#include "Highscores.h"

const uint32_t Highscores::maxScore = 12;

void Highscores::add(const HighscoreEntry& entry)
{
    m_highscores.insert(entry);
}

uint32_t Highscores::size()
{
    return (m_highscores.size() <= Highscores::maxScore) ?
        m_highscores.size() : Highscores::maxScore;
}

const HighscoreEntry& Highscores::get(uint32_t index)
{
    auto it = m_highscores.begin();
    for (uint32_t i = 0; i < index; i++)
    {
        std::advance(it, 1);
    }
    return *it;
}

void Highscores::save()
{
    for (const auto& hs : m_highscores)
    {
        std::string str = hs.name +
                          " " +
                          std::to_string(hs.score) +
                          " " +
                          hs.timestamp;
        if (m_encryptor)
        {
            str = m_encryptor->encrypt(str);
        }
        m_dataStorage->writeLine(str);
    }
}
