#ifndef PLAYER_H_DEFINDED
#define PLAYER_H_DEFINDED

class Player
{
public:
    Player(int m_score);
    ~Player();

    int getScore();
    void setScore(int m_score);

private:
    int score;
};

#endif
