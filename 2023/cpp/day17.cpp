#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

typedef std::pair<int, int> coordinate;

struct PathState {
    int pathLength;
    coordinate position;
    std::pair<int, int> direction;
    int directionStepsNumber;

    bool operator>(const PathState& other) const {
        return pathLength > other.pathLength;
    }
};

int part01(std::map<coordinate, int> &lossMap,coordinate start, coordinate end) {
    std::priority_queue<PathState, std::vector<PathState>, std::greater<PathState>> activePath;
    std::map<std::tuple<std::pair<int, int>, std::pair<int, int>, int>, int> goodList;
    std::map<std::tuple<std::pair<int, int>, std::pair<int, int>, int>, int> badList;

//start directions
    
    std::pair<int,int> directionStart{0,1};//desno
    activePath.push({0,start,directionStart,0});
    goodList[{start, directionStart, 0}] = 0;
    directionStart = std::make_pair(1, 0);//dole
    activePath.push({0,start,directionStart,0});
    goodList[{start, directionStart, 0}] = 0;

    while (!activePath.empty()) {
        PathState current = activePath.top();
        activePath.pop();
        goodList.erase({current.position, current.position, current.directionStepsNumber});

        if (current.position == end) {
            return current.pathLength;
        }

        for (auto delta : std::vector<std::pair<int, int>>{current.position, {current.position.second, -current.position.first}, {-current.position.second, current.position.first}}) {
            auto newPosition = std::make_pair(current.position.first + delta.first, current.position.second + delta.second);

            if (lossMap.find(newPosition) == lossMap.end()) {
                continue;
            }

            auto newDirectionSteps = (delta == current.position) ? current.directionStepsNumber + 1 : 0;

            if (newDirectionSteps == 3) {
                continue;
            }

            auto newPathLen = current.pathLength + lossMap[newPosition];

            auto newPath =PathState{newPathLen, newPosition, delta, newDirectionSteps};
            auto newPathTuple = std::make_tuple(newPosition, delta, newDirectionSteps);

            if (goodList.find(newPathTuple) != goodList.end() && goodList[newPathTuple] <= newPathLen) {
                continue;
            }

            if (badList.find(newPathTuple) != badList.end() && badList[newPathTuple] <= newPathLen) {
                continue;
            }

            activePath.push(newPath);
            goodList[newPathTuple] = newPathLen;
        }

        badList[{current.position, current.position, current.directionStepsNumber}] = current.pathLength;
    }

    return 0;
}

int part02(std::map<std::pair<int, int>, int> &lossMap, std::pair<int, int> start, std::pair<int, int> end) {
    std::priority_queue<PathState, std::vector<PathState>, std::greater<PathState>> activePath;
    std::map<std::tuple<std::pair<int, int>, std::pair<int, int>, int>, int> goodList;
    std::map<std::tuple<std::pair<int, int>, std::pair<int, int>, int>, int> badList;

    for (auto d : std::vector<std::pair<int, int>>{{0, 1}, {1, 0}}) {
        activePath.push({0, start, d, 0});
        goodList[{start, d, 0}] = 0;
    }

    while (!activePath.empty()) {
       PathState current = activePath.top();
        activePath.pop();
        goodList.erase({current.position, current.position, current.directionStepsNumber});

        if (current.position == end && current.directionStepsNumber >= 3) {
            return current.pathLength;
        }

        auto new_dirs = (current.directionStepsNumber< 3) ? std::vector<std::pair<int, int>>{current.position} : std::vector<std::pair<int, int>>{current.position, {current.position.second, -current.position.first}, {-current.position.second, current.position.first}};

        for (auto delta : new_dirs) {
            auto newPosition = std::make_pair(current.position.first + delta.first, current.position.second + delta.second);

            if (lossMap.find(newPosition) == lossMap.end()) {
                continue;
            }

            auto newDirectionSteps = (delta == current.position) ? current.directionStepsNumber + 1 : 0;

            if (newDirectionSteps == 10) {
                continue;
            }

            auto newPathLen = current.pathLength + lossMap[newPosition];

            auto newPath =PathState{newPathLen, newPosition, delta, newDirectionSteps};
            auto newPathTuple = std::make_tuple(newPosition, delta, newDirectionSteps);

            if (goodList.find(newPathTuple) != goodList.end() && goodList[newPathTuple] <= newPathLen) {
                continue;
            }

            if (badList.find(newPathTuple) != badList.end() && badList[newPathTuple] <= newPathLen) {
                continue;
            }

            activePath.push(newPath);
            goodList[newPathTuple] = newPathLen;
        }

        badList[{current.position, current.position, current.directionStepsNumber}] = current.pathLength;
    }

    return -0;
}



int main() {
    
    std::ifstream inputFile("../input/day17.txt");
    std::vector<std::string> inputLines;
    std::string inputLine;

    while(std::getline(inputFile,inputLine)) {
        inputLines.push_back(inputLine);
    }
    inputFile.close();
    int rowSize=inputLines.size();
    int colSize=inputLines[1].size();
    std::map<std::pair<int, int>, int> lossMap;
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            lossMap[{j, i}] = inputLines[i][j] - '0';
        }
    }

    auto start = std::make_pair(0, 0);
    auto end = std::make_pair(inputLines[0].size() - 1, inputLines.size() - 1);

    int part1 = part01(lossMap, start, end);
    std::cout << "Part01: " << part1 << std::endl;
    int part2 = part02(lossMap, start, end);
    std::cout << "Part02: " << part2 << std::endl;

    return 0;
}
