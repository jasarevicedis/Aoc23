#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


typedef std::pair<int, int> Point;

int dr[] = { -1, 1, 0, 0 }, dc[] = { 0, 0, -1 ,1 };
std::string steepSlopes = "><v^";



auto canGo(std::vector<std::string> inputLines, int row, int col, bool sliperry, int dir_index){
    return row >= 0 && row < inputLines.size() && inputLines[row][col] != '#' &&
        (!sliperry || steepSlopes.find(inputLines[row][col]) != dir_index);
}

auto findForks(std::vector<std::string> inputLines){
    std::vector<std::pair<int,int>> retval;

    for (int i = 0; i < inputLines.size(); i++)
        for (int j = 0; j < inputLines[0].size(); j++){
            if (inputLines[i][j] == '#')
                continue;

            if (i == 0 || i == inputLines.size() - 1){
                retval.push_back({ i, j });
                continue;
            }

            auto wayNumber = 0;
            for (auto k = 0; k < 4; k++)
                if (inputLines[i + dr[k]][j + dc[k]] != '#')
                    wayNumber++;

            if (wayNumber > 2)
                retval.push_back({ i, j });
        }

    return retval;
}

auto followTunnel(std::vector<std::string> inputLines, std::vector<Point> &forks, int index, int rdir, int cdir, bool slippery){
    Point &fork = forks[index];
    auto prev_row = fork.first, prev_col = fork.second;
    auto row = fork.first + rdir, col = fork.second + cdir;

    for (int len = 1; ; len++){
        auto found = std::find_if(forks.begin(), forks.end(),
            [row, col](Point &fork) {return fork.first == row && fork.second == col; });
        if (found != forks.end())
            return make_pair(found, len);

        auto next_row = -1, next_col = -1;
        for (int i = 0; i < 4; i++){
            next_row = row + dr[i], next_col = col + dc[i];

            if ((next_row != prev_row || next_col != prev_col) && canGo(inputLines, next_row, next_col, slippery, i))
                break;
        }

        if (next_row == -1 && next_col == -1)
            return make_pair(forks.end(), -1);

        prev_row = row, prev_col = col;
        row = next_row, col = next_col;
    }
}

auto buildAdjacencyMatrix(std::vector<std::string> inputLines, std::vector<Point> &forks, bool respect_slope){
    std::vector<std::vector<int>> adj(forks.size(), std::vector<int>(forks.size()));

    for (int i = 0; i < forks.size(); i++)
        for (int j = 0; j < 4; j++){
            auto row = forks[i].first + dr[j], col = forks[i].second + dc[j];

            if (canGo(inputLines, row, col, respect_slope, j)){
                auto end = followTunnel(inputLines, forks, i, dr[j], dc[j], respect_slope);
                if (end.second != -1)
                    adj[i][end.first - forks.begin()] = end.second;
            }
        }

    return adj;
}

auto solve(std::vector<std::string> inputLines, bool slippery){
    auto forks = findForks(inputLines);
    auto adj = buildAdjacencyMatrix(inputLines, forks, slippery);
    auto maxPath = 0;

    auto seen = std::vector<bool>(forks.size());
    seen[0] = true;

    auto recursion = [&](auto &self, int distance, int start_index){
        if (start_index == adj.size() - 1){
            maxPath = std::max(maxPath, distance);
            return;
        }

        for (int i = 0; i < adj[start_index].size(); i++)
            if (adj[start_index][i] && !seen[i]){
                seen[i] = true;
                self(self, distance + adj[start_index][i], i);
                seen[i] = false;
            }
    };

    recursion(recursion, 0, 0);
    return maxPath;
}

int main(){
    std::ifstream inputFile("../input/day23.txt");
    std::string inputLine;
    std::vector<std::string> inputLines;

    while (std::getline(inputFile, inputLine))
        inputLines.push_back(inputLine);

    

    auto part1 = solve(inputLines, true);
    std::cout << "Part One: " << part1 << std::endl;

    auto part2 = solve(inputLines, false);
    std::cout << "Part Two: " << part2 << std::endl;

 
    return 0;
}
