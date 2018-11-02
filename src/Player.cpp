#include <Player.hpp>

Player::Player(int m_score, std::string m_name):
    score(m_score),
    name(m_name)
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
std::string Player::getName()
{
    return this->name;
}
