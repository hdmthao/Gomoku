#ifndef LOADSTAT_H_DEFINED
#define LOADSTAT_H_DEFINED

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::pair;

class LoadStat {
public:

    static string namePlayer1;
    static string namePlayer2;
    static int XIcon;
    static int OIcon;
    static string gameMode;
    static int size;
    static int gameRule;
    static int scorePlayer1;
    static int scorePlayer2;
    static int countGame;
    static vector<pair<int, int>> score;
    static vector< vector<pair< pair<int, int>, int>> > board;

    static void saveStat(string filename, string namePlayer1, string namePlayer2, bool aiMod, int size, int gameRule, int scorePlayer1, int scorePlayer2, int countGame, vector<pair<int, int>> score, vector< vector<pair<int, int> > > board);

    static vector<string> listGames();
    static void load(string filename);
    static string getNamePlayer(int curr);
    static vector< vector< pair<pair<int, int>, int> > > loadBoard();

    static int getInt(string str);
    static vector< pair<pair<int, int>, int> > getBoard(string str);
};
#endif
