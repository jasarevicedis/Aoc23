#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <tuple>

typedef std::vector<std::vector<std::vector<bool>>> visitMatrix;

enum Direction {
    UP, RIGHT, DOWN, LEFT
};

Direction mirror1[] = {RIGHT, UP, LEFT, DOWN};
Direction mirror2[] = {LEFT, DOWN, RIGHT, UP};

void simulateBeam(std::vector<std::string> map, int startY, int startX,visitMatrix &visited, Direction startDirection) {
    std::queue<std::tuple<int, int, Direction>> next;
    next.push(std::make_tuple(startY, startX, startDirection));

    while (!next.empty()) {
        std::tuple<int, int, Direction> temp = next.front();
        next.pop();
        
        int y = std::get<0>(temp);
        int x = std::get<1>(temp);
        Direction direction = std::get<2>(temp);
        auto &field = visited[direction];
        int dx = 0;
        int dy = 0;

        if (direction == UP)
            dy = -1;
        else if (direction == DOWN)
            dy = 1;
        else if (direction == LEFT)
            dx = -1;
        else if (direction == RIGHT)
            dx = 1;

        while (y + dy >= 0 && y + dy < field.size() && x + dx >= 0 && x + dx < field[0].size()){
            y = y + dy;
            x = x + dx;
            if (field[y][x])
                break;
            field[y][x] = true;

            if (map[y][x] == '/') {
                next.push(std::make_tuple(y, x, mirror1[direction]));
                break;
            } else if (map[y][x] == '\\') {
                next.push(std::make_tuple(y, x, mirror2[direction]));
                break;
            } else if (map[y][x] == '-' && dx == 0) {
                next.push(std::make_tuple(y, x, LEFT));
                next.push(std::make_tuple(y, x, RIGHT));
                break;
            } else if (map[y][x] == '|' && dy == 0) {
                next.push(std::make_tuple(y, x, UP));
                next.push(std::make_tuple(y, x, DOWN));
                break;
            }
        }
    }
}

int calculateEnergized(std::vector<std::string> inputLines, int y, int x, Direction direction) {
    visitMatrix visited(4, std::vector<std::vector<bool>>(inputLines.size(), std::vector<bool>(inputLines[0].size(), false)));

    simulateBeam(inputLines, y, x,visited, direction);

    int sum = 0;
    int rowSize= inputLines.size();
    int colSize= inputLines[0].size();
    for (int y = 0; y < rowSize; y++){
        for (int x = 0; x < colSize; x++){
            if (visited[UP][y][x] || visited[RIGHT][y][x] || visited[DOWN][y][x] || visited[LEFT][y][x])
                sum++;
        }
    }

    return sum;
}

void part01(std::vector<std::string> inputLines) {
    int count = calculateEnergized(inputLines, 0, -1, RIGHT);
    std::cout << "Part01: " << count << std::endl;
}

void part02(std::vector<std::string> inputLines) {
    int largest = 0;

    for (int x = 0; x < inputLines[0].size(); x++) {
        int count = calculateEnergized(inputLines, -1, x, DOWN);
        if (count > largest) 
            largest = count;
        count = calculateEnergized(inputLines, inputLines.size(), x, UP);
        if (count > largest) 
            largest = count;
    }

    for (int y = 0; y < inputLines.size(); y++) {
        int count = calculateEnergized(inputLines, y, -1, RIGHT);
        if (count > largest) 
            largest = count;
        count = calculateEnergized(inputLines, y, inputLines[0].size(), LEFT);
        if (count > largest) 
            largest = count;
    }

    std::cout << "Part02: " <<  largest;
}





int main() {
    std::ifstream inputFile("../input/day16.txt");
    std::vector<std::string> inputLines;
    std::string inputLine;
    while(std::getline(inputFile,inputLine)) {
        inputLines.push_back(inputLine);
    }
    inputFile.close();

    part01(inputLines);
    part02(inputLines);

    return 0;
}
