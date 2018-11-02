#ifndef LOADGAME_H_DEFINED
#define LOADGAME_H_DEFINED

#include <string>
#include <vector>

class LoadGame {
public:

    static int score1;
    static int score2;
    static int width;
    static int height;
    static int lastPlayer;
    static std::string namePlayer1;
    static std::string namePlayer2;
    static std::string str;

    static void load(std::string filename);
    static int loadScore(int currentPlayer);
    static std::string loadName(int currentPlayer);
    static int loadTypeBoard();
    static int loadLastPlayer();
    static void removeLoadGame(std::string filename);
    static std::vector< std::vector<char> > loadBoard();
    static std::vector< std::pair<std::pair<int, int>, char> > loadContainBoard();
    static void saveGame(std::string filename, std::string namePlayer1, std::string namePlayer2, int m_score1, int m_score2, int size, int currentPlayer, std::vector< std::pair<int, int> > board);

    static int getInt(std::string str);
	static std::vector<std::string> listGames();
	static std::vector<std::string> listInfos();
};

#endif
