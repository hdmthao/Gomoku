#include <Player.hpp>

Player::Player(int m_score):
    score(m_score)
{ }
Player::~Player()
{ }
void Player::setScore(int m_score)
{
    this->score = m_score;
}
int Player::getScore()
{
    return this->score;
}
