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
    static bool isAiMod;
    static int gameRule;
    static std::string str;

    static int rating;
    static int playedGameMul;
    static int playedGameCamp;
    static int winGame;
    static std::string winRate;
    static std::string topCharacterMoba;
    static std::string topCharacterMarvel;
    static std::string name[20];
    static int count[20];

    static void load(std::string filename);
    static int loadScore(int currentPlayer);
    static std::string loadName(int currentPlayer);
    static int loadTypeBoard();
    static int loadLastPlayer();
    static bool loadMode();
    static int loadGameRule();

    static void removeLoadGame(std::string filename);
    static std::vector< std::vector<char> > loadBoard();
    static std::vector< std::pair<std::pair<int, int>, char> > loadContainBoard();
    static void saveGame(std::string filename, std::string namePlayer1, std::string namePlayer2, bool m_aimod, int m_gameRule, int m_score1, int m_score2, int size, int currentPlayer, std::vector< std::pair<int, int> > board);

    static void saveStatictis();
    static void loadStatictis();
    static int loadRating();
    static int loadPlayedMul();
    static int loadPlayedCamp();
    static int loadWin();
    static std::string loadWinRate();
    static std::string loadMoba();
    static std::string loadMarvel();
    static std::string getName(std::string str);

    static int getInt(std::string str);
    static std::string getStr(std::string str);
	static std::vector<std::string> listGames();
	static std::vector<std::string> listInfos();
};

#endif
