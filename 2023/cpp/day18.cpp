#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

typedef unsigned long long ull;
enum Direction {
    RIGHT, DOWN, LEFT, UP
};
int directionsY[] = {0, 1, 0, -1};
int directionsX[] = {1, 0, -1, 0};

//first time hearing about this formula, had to google this things
std::tuple<std::vector<std::tuple<ull, ull>>, ull> createPolygon(std::vector<std::tuple<Direction, ull>> digPlan){
    std::vector<std::tuple<ull , ull>> polygon;
    ull edge(0);
    ull y = 0;
    ull x = 0;
    for (auto &dig : digPlan){
        Direction direction = std::get<0>(dig);
        ull depth = std::get<1>(dig);
        y += depth * directionsY[direction];
        x += depth * directionsX[direction];
        edge += depth;

        polygon.push_back(std::make_tuple(y, x));
    }

    return make_tuple(polygon, edge);
}

ull area(std::vector<std::tuple<ull, ull>> polygon, ull edge){
    ull shoelace = 0;
    for (ull i = 0; i < polygon.size(); i++){
        ull next = (i + 1) % polygon.size();
        shoelace += std::get<1>(polygon[i]) * std::get<0>(polygon[next]) - std::get<0>(polygon[i]) * std::get<1>(polygon[next]);
    }
    shoelace = shoelace / 2;
    ull inner = shoelace - edge / 2 + 1;
    return edge + inner;
}

void part01(std::vector<std::tuple<Direction, ull>> digPlan){
    auto result = createPolygon(digPlan);
    std::vector<std::tuple<ull, ull>> polygon = std::get<0>(result);
    ull edgeLen = std::get<1>(result);
    std::cout << "Part01: " <<  area(polygon, edgeLen) << std::endl;
}

void part02(const std::vector<std::string> &hexes){
    std::vector<std::tuple<Direction, ull>> digPlan;

    for (const auto &c: hexes){
        ull len = strtol(c.substr(0, 5).c_str(), nullptr, 16);
        Direction dir = static_cast<Direction>(strtol(c.substr(5).c_str(), nullptr, 16));

        digPlan.push_back(std::make_tuple(dir, len));
    }

    std::tuple<std::vector<std::tuple<ull, ull>>, ull> result = createPolygon(digPlan);
    std::vector<std::tuple<ull, ull>> polygon = std::get<0>(result);
    ull edgeLen = std::get<1>(result);

    std::cout << "Part02: " <<  area(polygon, edgeLen);
}



int main() {
    std::ifstream inputFile("../input/day18.txt");
    std::string inputLine;
    std::vector<std::tuple<Direction, ull>> digPlan;
    std::vector<std::string> hexs;
    while(std::getline(inputFile,inputLine)) {
        Direction direction;
        switch (inputLine[0]) {
            case 'U': 
                direction = UP; 
                break;
            case 'D': 
                direction = DOWN; 
                break;
            case 'L': 
                direction = LEFT; 
                break;
            case 'R': 
                direction = RIGHT; 
                break;
        }

        ull position = inputLine.find(' ', 2);
        ull depth = std::stoi(inputLine.substr(2, position - 2));

        std::string hex = inputLine.substr(position + 3, inputLine.find(')') - position - 3);

        digPlan.push_back(std::make_tuple(direction, depth));
        hexs.push_back(hex);
    }
    inputFile.close();

    part01(digPlan);
    part02(hexs);

    return 0;
}
