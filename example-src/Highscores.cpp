#include "Highscores.h"

void Highscores::add(const HighscoreEntry& entry)
{
    m_highscores.insert(entry);
}

uint32_t Highscores::size()
{
    return m_highscores.size();
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
        m_dataStorage->writeLine(str);
    }
}
