#include <LoadStat.hpp>
#include <EngineGlobals.hpp>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <langinfo.h>

const string path = "/home/himt/cs/cs161/projects/Gomoku/src/History/";


string LoadStat::namePlayer1 = "";
string LoadStat::namePlayer2 = "";
int LoadStat::XIcon = (int)'X';
int LoadStat::OIcon = (int)'O';
string LoadStat::gameMode = "";
int LoadStat::size = 0;
int LoadStat::gameRule = 0;
int LoadStat::scorePlayer1 = 0;
int LoadStat::scorePlayer2 = 0;
int LoadStat::countGame = 0;
vector<pair<int, int>> LoadStat::score;
vector< vector<pair< pair<int, int>, int>> > LoadStat::board;

vector<string> LoadStat::listGames()
{
    vector<string> infos;
    DIR* dir;

    dir = opendir(path.c_str());
    struct dirent* ent;
    struct stat statbuf;
    struct tm* tm;
    char datestring[100];
    char timestring[100];
    string fullpath="";
    while ((ent = readdir(dir)))
    {
        string s = ent->d_name;
        if (s == "." || s == "..") continue;
        string fullpath = path + s;

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

        for (int i = s.length() - 1; i >= 0; --i) {
            if (s[i] != '.') {
                s.erase(i, 1);
            } else {
                s.erase(i, 1);
                break;
            }
        }
        s = s + " ";

        infos.push_back(s + timestring);
    }
    closedir(dir);
    return infos;
}
void LoadStat::saveStat(string filename, string namePlayer1, string namePlayer2, bool aiMod, int size, int gameRule, int scorePlayer1, int scorePlayer2, int countGame, vector<pair<int, int> > score, vector< vector<pair<int, int> > > board)
{
    filename = path + filename + ".txt";
    std::ofstream file;
    file.open(filename);
    file << namePlayer1 << "\n";
    file << namePlayer2 << "\n";
    file << "\"player1_icon\":" << EngineGlobals::Board::XIcon << "\n";
    file << "\"player2_icon\":" << EngineGlobals::Board::OIcon << "\n";
    if (aiMod) file << "Campaign" << "\n";
    else file << "Multiplayer" << "\n";
    file << "\"size\":" << size << "\n";
    file << "\"game_rule\":" << gameRule << "\n";
    file << "\"player1_score\":" << scorePlayer1 << "\n";
    file << "\"player2_score\":" << scorePlayer2 << "\n";
    file << "\"count_game\":" << countGame << "\n";
    for (int k = 0; k < countGame; ++k)
    {
        file << "\"player1_score_round" << k + 1 << "\":" << score[k].first << "\n";
        file << "\"player2_score_round" << k + 1 << "\":" << score[k].second << "\n";
        for (unsigned int j = 0; j < board[k].size(); ++j) {
            pair<int, int> ii;
            ii = board[k][j];
            file << ii.first << " " << ii.second << " ";
        }
        file << "\n";
    }
    file.close();
}
void LoadStat::load(string filename)
{
    score.clear();
    board.clear();
    filename = path + filename + ".txt";
    std::ifstream file(filename);
    string line;
    int countLine = 0;
    int countLine2 = 0;
    int score1 = 0;
    int score2 = 0;
    while (std::getline(file, line))
    {
        countLine++;
        if (countLine == 1) LoadStat::namePlayer1 = line;
        if (countLine == 2) LoadStat::namePlayer2 = line;
        if (countLine == 3) LoadStat::XIcon = LoadStat::getInt(line);
        if (countLine == 4) LoadStat::OIcon = LoadStat::getInt(line);
        if (countLine == 5) LoadStat::gameMode = line;
        if (countLine == 6) LoadStat::size = LoadStat::getInt(line);
        if (countLine == 7) LoadStat::gameRule = LoadStat::getInt(line);
        if (countLine == 8) LoadStat::scorePlayer1 = LoadStat::getInt(line);
        if (countLine == 9) LoadStat::scorePlayer2 = LoadStat::getInt(line);
        if (countLine == 10) LoadStat::countGame = LoadStat::getInt(line);
        if (countLine > 10) {
            countLine2++;
            if (countLine2 % 3 == 1) score1 = LoadStat::getInt(line);
            if (countLine2 % 3 == 2) score2 = LoadStat::getInt(line);
            if (countLine2 % 3 == 0) {
                score.push_back(std::make_pair(score1, score2));
                board.push_back(LoadStat::getBoard(line));
            }
        }
    }
    file.close();
}
string LoadStat::getNamePlayer(int curr)
{
    if (curr == 1) return LoadStat::namePlayer1; else return LoadStat::namePlayer2;
}
int LoadStat::getInt(string str)
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
vector< pair< pair<int, int>, int> > LoadStat::getBoard(string line) {
    vector< pair< pair<int, int>, int> > vec;

    unsigned int cnt = 0;
    int x = 0;
    int y = 0;
    int num = 0;
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
            y = num % LoadStat::size;
            x = num / LoadStat::size + 1;
            if (num % LoadStat::size == 0)
            {
                y += LoadStat::size;
                x--;
            }
            int tmp;
            if (line[i] == '1') tmp =1;
            if (line[i] == '2') tmp =2;
            if (line[i] == '3') tmp =3;
            if (line[i] == '4') tmp = 4;
            vec.push_back(std::make_pair(std::make_pair(x, y), tmp));
            num = 0;
        }
    }
    return vec;
}
