#ifndef PLAYER_H_DEFINDED
#define PLAYER_H_DEFINDED
#include <string>

class Player
{
public:
    Player(int m_score, std::string m_name);
    ~Player();

    int getScore();
    void setScore(int m_score);
    std::string getName();

private:
    int score;
    std::string name;
};

#endif
