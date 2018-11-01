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

const std::string path = "/home/himt/cs/cs161/projects/Gomoku/src/Save/";

int LoadGame::score1 = 0;
int LoadGame::score2 = 0;
int LoadGame::width = 0;
int LoadGame::height = 0;
int LoadGame::lastPlayer = 1;
std::string LoadGame::str = "";
void LoadGame::saveGame(std::string m_filename, int m_score1, int m_score2, int size, int currentPlayer, std::vector<std::pair<int, int> > board)
{
    std::string filename = path + m_filename + ".txt";
    std::ofstream file;
    file.open(filename);

    file << "player1_score=" << m_score1 << "\n";
    file << "player2_score=" << m_score2 << "\n";
    file << "height=" << size << "\n";
    file << "width=" << size << "\n";
    file << "last_player=" << currentPlayer << "\n";
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
        if (countLine == 1) LoadGame::score1 = LoadGame::getInt(line);
        if (countLine == 2) LoadGame::score2 = LoadGame::getInt(line);
        if (countLine == 3) LoadGame::width = LoadGame::getInt(line);
        if (countLine == 4) LoadGame::height = LoadGame::getInt(line);
        if (countLine == 5) LoadGame::lastPlayer = LoadGame::getInt(line);
        if (countLine == 6) LoadGame::str = line;
    }
}
int LoadGame::loadScore(int currentPlayer)
{
    if (currentPlayer == 1) return LoadGame::score1;
    else return LoadGame::score2;
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
        if (str[i] == '=') break;
    }
    int num = 0;
    ++i;
    while (i != str.length()) {
        num = num * 10 + (str[i] - '0');
        ++i;
    }
    return num;
}
int LoadGame::loadLastPlayer()
{
    return LoadGame::lastPlayer;
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
