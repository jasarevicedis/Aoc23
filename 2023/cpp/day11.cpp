#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>//for int abs function

typedef unsigned long long ull;//everywhere beacuse of part2, maybe unnecessary

struct Coordinate {
    ull x,y;
};

std::vector<Coordinate> expandSpace(std::vector<Coordinate> &galaxies, int expansionValue)
{
    std::vector<Coordinate> expanded;

    std::vector<bool> usedCols(140, false);
    std::vector<bool> usedRows(140, false);
    for (auto &g : galaxies) {
        usedCols[g.y] = true;
        usedRows[g.x] = true;
    }

    std::vector<ull> rowOffsets(140, 0);
    ull rowOffset = 0;
    std::vector<ull> colOffsets(140, 0);
    ull colOffset = 0;
    for (int i = 0; i < 140; i++) {
        if (!usedCols[i])
            colOffset += expansionValue - 1;
        colOffsets[i] = colOffset;
        if (!usedRows[i])
            rowOffset += expansionValue - 1;
        rowOffsets[i] = rowOffset;

    }

    for (auto &g : galaxies)
        expanded.push_back({g.x + rowOffsets[g.x], g.y + colOffsets[g.y]});

    return expanded;
}

void part01(std::vector<std::string> inputLines) {
    ull columnNum = inputLines.at(0).size();
    ull rowNum = inputLines.size();
    std::vector<Coordinate> galaxies;
    std::vector<ull> shortestPaths;
    std::vector<Coordinate> expandedSpace;


    columnNum=inputLines.at(0).size();
    rowNum=inputLines.size();
    for(ull i=0;i< rowNum;i++){
        for(ull j=0;j<columnNum;j++){
            if(inputLines.at(i).at(j) == '#')
                galaxies.push_back({i,j});
        }
    }

    //DOUBLING THE ROWS and COLUMNS
    expandedSpace = expandSpace(galaxies, 2);
    //---------------------------------------------

    //std::cout << "---" << galaxies.size() <<std::endl;
    ull path(0);
    ull size =expandedSpace.size();
    for(ull i=0;i< size;i++){
        for(ull j=i+1;j<size;j++){
            path = std::abs(long(expandedSpace.at(i).x - expandedSpace.at(j).x)) + std::abs(long(expandedSpace.at(i).y - expandedSpace.at(j).y));
            
            shortestPaths.push_back(path);
        }
    }
    int sum(0);
    for(int p:shortestPaths)
        sum+=p;
    std::cout << "Part 01: " << sum << std::endl;
}


void part02(std::vector<std::string> inputLines) {
    ull columnNum = inputLines.at(0).size();
    ull rowNum = inputLines.size();
    std::vector<Coordinate> galaxies;
    std::vector<ull> shortestPaths;
    std::vector<Coordinate> expandedSpace;


    columnNum=inputLines.at(0).size();
    rowNum=inputLines.size();
    for(ull i=0;i< rowNum;i++){
        for(ull j=0;j<columnNum;j++){
            if(inputLines.at(i).at(j) == '#')
                galaxies.push_back({i,j});
        }
    }

    //DOUBLING THE ROWS and COLUMNS
    expandedSpace = expandSpace(galaxies, 1000000);
    //---------------------------------------------

    //std::cout << "---" << galaxies.size() <<std::endl;
    ull path(0);
    ull size =expandedSpace.size();
    for(ull i=0;i< size;i++){
        for(ull j=i+1;j<size;j++){
            path = std::abs(long(expandedSpace.at(i).x - expandedSpace.at(j).x)) + std::abs(long(expandedSpace.at(i).y - expandedSpace.at(j).y));
            
            shortestPaths.push_back(path);
        }
    }
    ull sum(0);
    for(ull p:shortestPaths)
        sum+=p;
    std::cout << "Part 02: " << sum << std::endl;
}

int main() {
    std::ifstream inputFile("../input/day11.txt");
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
