#include <LoadGame.hpp>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <langinfo.h>
#include <iomanip>

const std::string path = "/home/himt/cs/cs161/projects/Gomoku/src/Save/";
const std::string pathStats = "/home/himt/cs/cs161/projects/Gomoku/src/Statistic/stats.txt";

int LoadGame::score1 = 0;
int LoadGame::score2 = 0;
int LoadGame::width = 0;
int LoadGame::height = 0;
int LoadGame::lastPlayer = 1;
std::string LoadGame::namePlayer1 = "";
std::string LoadGame::namePlayer2 = "";
bool LoadGame::isAiMod = false;
int LoadGame::gameRule = 0;
std::string LoadGame::str = "";

int LoadGame::rating = 0;
int LoadGame::playedGameMul = 0;
int LoadGame::playedGameCamp = 0;
int LoadGame::winGame = 0;
std::string LoadGame::winRate = "";
std::string LoadGame::topCharacterMoba = "";
std::string LoadGame::topCharacterMarvel = "";
int LoadGame::count[20] = {0};
std::string LoadGame::name[20] = {""};

void LoadGame::saveGame(std::string m_filename, std::string namePlayer1, std::string namePlayer2, bool m_aimod, int m_gameRule, int m_score1, int m_score2, int size, int currentPlayer, std::vector<std::pair<int, int> > board)
{
    std::string filename = path + m_filename + ".txt";
    std::ofstream file;
    file.open(filename);

    file << namePlayer1 << "\n";
    file << namePlayer2 << "\n";
    file << "\"player1_score\":" << m_score1 << "\n";
    file << "\"player2_score\":" << m_score2 << "\n";
    if (m_aimod)
        file << "\"game_mod\":" << 1 << "\n";
    else
        file << "\"game_mod\":" << 0 << "\n";
    file << "\"game_rule\":" << m_gameRule << "\n";
    file << "\"height\":" << size << "\n";
    file << "\"width\":" << size << "\n";
    file << "\"last_player\":" << currentPlayer << "\n";
    for (unsigned int i = 0; i < board.size(); ++i) {
        std::pair<int, int> ii;
        ii = board[i];
        file << ii.first << " " << ii.second << " ";
    }
    file.close();
}
void LoadGame::load(std::string filename)
{
    if (filename.empty()) return;
    filename = path + filename + ".txt";
    std::ifstream file;
    file.open(filename);

    std::string line = "";
    int countLine = 0;
    while (std::getline(file, line)) {
        ++countLine;
        if (countLine == 1) LoadGame::namePlayer1 = line;
        if (countLine == 2) LoadGame::namePlayer2 = line;
        if (countLine == 3) LoadGame::score1 = LoadGame::getInt(line);
        if (countLine == 4) LoadGame::score2 = LoadGame::getInt(line);
        if (countLine == 5) LoadGame::isAiMod = LoadGame::getInt(line);
        if (countLine == 6) LoadGame::gameRule = LoadGame::getInt(line);
        if (countLine == 7) LoadGame::width = LoadGame::getInt(line);
        if (countLine == 8) LoadGame::height = LoadGame::getInt(line);
        if (countLine == 9) LoadGame::lastPlayer = LoadGame::getInt(line);
        if (countLine == 10) LoadGame::str = line;
    }
}
int LoadGame::loadScore(int currentPlayer)
{
    if (currentPlayer == 1) return LoadGame::score1;
    else return LoadGame::score2;
}
std::string LoadGame::loadName(int currentPlayer)
{
    if (currentPlayer == 1) return LoadGame::namePlayer1;
    else return LoadGame::namePlayer2;
}
int LoadGame::loadGameRule()
{
    return LoadGame::gameRule;
}
int LoadGame::loadTypeBoard()
{
    switch (LoadGame::width)
    {
        case 3:
            return 1;
            break;
        case 9:
            return 2;
            break;
        case 13:
            return 3;
            break;
        case 19:
            return 4;
            break;
        default:
            return 0;
            break;
    }
}
std::vector< std::vector<char> > LoadGame::loadBoard()
{
    std::vector< std::vector<char> > board;
    board.resize(LoadGame::height + 1);
    for (int i = 1; i <= LoadGame::height; ++i)
    {
        board[i].resize(LoadGame::width + 1);
    }

    unsigned int cnt = 0;
    int x = 0;
    int y = 0;
    int num = 0;
    std::string line = LoadGame::str;
    for (unsigned int i = 0; i < line.length(); ++i) {
        if (line[i] == ' ')
        {
            ++cnt;
            continue;
        }
        if (cnt % 2 == 0)
            num = num*10 + (line[i] - '0');
        else
        {
            y = num % LoadGame::width;
            x = num / LoadGame::width + 1;
            if (num % LoadGame::width == 0)
            {
                y += LoadGame::width;
                x--;
            }
            board[x][y] = line[i];
            num = 0;
        }
    }
    return board;
}
std::vector< std::pair<std::pair<int, int>, char> > LoadGame::loadContainBoard()
{
    std::vector< std::pair<std::pair<int, int>, char > > contains;

    unsigned int cnt = 0;
    int x = 0;
    int y = 0;
    int num = 0;
    std::string line = LoadGame::str;
    for (unsigned int i = 0; i < line.length(); ++i) {
        if (line[i] == ' ')
        {
            ++cnt;
            continue;
        }
        if (cnt % 2 == 0)
            num = num*10 + (line[i] - '0');
        else
        {
            y = num % LoadGame::width;
            x = num / LoadGame::width + 1;

            if (num % LoadGame::width == 0)
            {
                y += LoadGame::width;
                x--;
            }
            contains.push_back(std::make_pair(std::make_pair(x, y), line[i]));
            num = 0;
        }
    }
    return contains;
}
int LoadGame::getInt(std::string str)
{
    unsigned int i = 0;
    for (;; ++i) {
        if (str[i] == ':') break;
    }
    int num = 0;
    ++i;
    while (i != str.length()) {
        num = num * 10 + (str[i] - '0');
        ++i;
    }
    return num;
}
std::string LoadGame::getStr(std::string str)
{
    unsigned int i = 0;
    for (;; ++i)
        if (str[i] == ':') break;
    ++i;
    std::string tmp = "";
    for (;i < str.length(); ++i)
    {
        tmp = tmp + str[i];
    }
    return tmp;
}
int LoadGame::loadLastPlayer()
{
    return LoadGame::lastPlayer;
}
bool LoadGame::loadMode()
{
    return LoadGame::isAiMod;
}
std::vector<std::string> LoadGame::listGames()
{
	std::vector<std::string> games;

    DIR* dir;

    dir = opendir(path.c_str());
    struct dirent* ent;
    while ((ent = readdir(dir)))
    {
        std::string s = ent->d_name;
        if (s == "." || s == "..") continue;
        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] != '.') {
                s.erase(i, 1);
            } else {
                s.erase(i, 1);
                break;
            }
        }
        games.push_back(s);
    }
    closedir(dir);

	return games;
}
std::vector<std::string> LoadGame::listInfos()
{
	std::vector<std::string> infos;

    DIR* dir;

    dir = opendir(path.c_str());
    struct dirent* ent;
    struct stat statbuf;
    struct tm* tm;
    char datestring[100];
    char timestring[100];
    std::string fullpath="";
    while ((ent = readdir(dir)))
    {
        std::string s = ent->d_name;
        if (s == "." || s == "..") continue;
        std::string fullpath = path + s;
        stat(fullpath.c_str(), &statbuf);

        tm = localtime(&statbuf.st_mtime);

        strftime(timestring, sizeof(datestring), nl_langinfo(T_FMT), tm);

        for (int i = strlen(timestring) - 1; i >= 0; --i) {
            if (timestring[i] != ':') {
                timestring[i] = '\0';
            }
            else
            {
                timestring[i] = ' ';
                break;
            }
        }

        strftime(datestring, sizeof(datestring), nl_langinfo(D_FMT), tm);
        strcat(timestring, datestring);
        infos.push_back(timestring);
    }
    closedir(dir);
	return infos;
}
void LoadGame::removeLoadGame(std::string filename)
{
    std::string tmp = "";
    for (unsigned int i = 0; i < filename.length(); ++i) {
        if (filename[i] == ' ') break;
        tmp += filename[i];
    }
    filename = path + tmp + ".txt";

    std::string command = "rm -f " + filename;

    system(command.c_str());
}
void LoadGame::saveStatictis()
{
    std::ofstream fileout;
    fileout.open(pathStats);
    fileout << "\"rating\":" << LoadGame::rating<< "\n";
    fileout << "\"played_game_mul\":" << LoadGame::playedGameMul<< "\n";
    fileout << "\"played_game_camp\":" << LoadGame::playedGameCamp<< "\n";
    fileout << "\"win_game\":" << LoadGame::winGame<< "\n";
    if (LoadGame::playedGameCamp== 0)
    fileout << "\"win_rate\":" << 0 <<"\n";
    else
    fileout << "\"win_rate\":" << std::fixed << std::setprecision(2) << 1.0 * LoadGame::winGame / LoadGame::playedGameCamp << "\n";
    for (unsigned int i = 1; i <= 16; ++i)
    {
        fileout << "\"" << name[i] << "\":" << count[i] << "\n";
    }
    fileout.close();
}
void LoadGame::loadStatictis()
{
    std::ifstream file;
    file.open(pathStats);
    std::string line = "";
    int countLine = 0;
    int topMarvel = 0;
    int topMoba = 0;
    while (std::getline(file, line)) {
        ++countLine;
        if (countLine == 1) LoadGame::rating = LoadGame::getInt(line);
        if (countLine == 2) LoadGame::playedGameMul = LoadGame::getInt(line);
        if (countLine == 3) LoadGame::playedGameCamp = LoadGame::getInt(line);
        if (countLine == 4) LoadGame::winGame = LoadGame::getInt(line);
        if (countLine == 5) LoadGame::winRate = LoadGame::getStr(line);
        if (countLine > 5 && countLine <= 13)
        {
            LoadGame::count[countLine - 5] = LoadGame::getInt(line);
            LoadGame::name[countLine - 5] = LoadGame::getName(line);

            int tmp = LoadGame::getInt(line);
            if (LoadGame::count[countLine - 5] >= topMarvel)
            {
                topMarvel = LoadGame::count[countLine - 5];
                LoadGame::topCharacterMarvel = LoadGame::name[countLine - 5];
            }
        }
        if (countLine > 13 && countLine <= 21)
        {
            LoadGame::count[countLine - 5] = LoadGame::getInt(line);
            LoadGame::name[countLine - 5] = LoadGame::getName(line);

            if (LoadGame::count[countLine - 5] >= topMoba)
            {
                topMoba = LoadGame::count[countLine - 5];
                LoadGame::topCharacterMoba = LoadGame::name[countLine - 5];
            }
        }
    }
}
int LoadGame::loadRating()
{
    return LoadGame::rating;
}
int LoadGame::loadPlayedCamp()
{
    return LoadGame::playedGameCamp;
}
int LoadGame::loadPlayedMul()
{
    return LoadGame::playedGameMul;
}

int LoadGame::loadWin()
{
    return LoadGame::winGame;
}
std::string LoadGame::loadWinRate()
{
    return LoadGame::winRate;
}
std::string LoadGame::loadMarvel()
{
    return LoadGame::topCharacterMarvel;
}
std::string LoadGame::loadMoba()
{
    return LoadGame::topCharacterMoba;
}
std::string LoadGame::getName(std::string str)
{
    std::string tmp = "";
    for (unsigned int i = 1; i < str.length(); ++i)
    {
        if (str[i] == '"') break;
        tmp += str[i];
    }
    return tmp;
}
