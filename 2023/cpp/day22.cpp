#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <limits>

struct Coordinate{
    int x, y, z;
    int coords[3];
    bool operator==(const Coordinate &other) const{
        return x == other.x && y == other.y && z == other.z;
    }
};

struct Brick{
    std::vector<Coordinate> coordinates;
    Coordinate start,end;
};

std::pair<std::vector<Brick>, int> dropAllBricks(std::vector<Brick> bricks){
    std::sort(bricks.begin(), bricks.end(), [](const Brick b1, const Brick b2){
        int min1 = std::numeric_limits<int>::max();
        for (auto block : b1.coordinates)
            min1 = std::min(min1, block.z);
        int min2 = std::numeric_limits<int>::max();
        for (auto block : b2.coordinates)
            min2 = std::min(min2, block.z);
        
        return min1 < min2; });

    std::vector<Coordinate> settled;
    std::vector<Brick> finalBricks;
    int numFell = 0;

    for (Brick brick : bricks){
        bool moved = false;
        while (true){
            std::vector<Coordinate> next;
            for (auto block : brick.coordinates)
                next.push_back({block.x, block.y, block.z - 1});

            if (all_of(next.begin(), next.end(), [&settled](const Coordinate &block)
                { return block.z != 0 && find(settled.begin(), settled.end(), block) == settled.end(); })){
                moved = true;
                brick.coordinates = next;
            }
            else
                break;
        }

        for (Coordinate block : brick.coordinates)
            settled.push_back(block);
        finalBricks.push_back(brick);
        if (moved)
            numFell++;
    }
    return {finalBricks, numFell};
}

int main(){
    std::ifstream inputFile("../input/day22.txt");
    std::string inputLine;

    std::vector<Brick> bricks;

    while (getline(inputFile, inputLine)){
        Brick temp;
        std::istringstream linestream(inputLine);
        linestream >> temp.start.x;
        linestream.ignore();
        linestream >> temp.start.y;
        linestream.ignore();
        linestream >> temp.start.z;
        linestream.ignore();
        linestream >> temp.end.x;
        linestream.ignore();
        linestream >> temp.end.x;
        linestream.ignore();
        linestream >> temp.end.x;
        linestream.ignore();
        std::vector<Coordinate> blocks;

        blocks.push_back(temp.start);

        for (int i = 0; i < 3; i++){
            if (temp.start.coords[i] != temp.end.coords[i]){
                for (int j = temp.start.coords[i] + 1; j < temp.end.coords[i]; j++){
                    Coordinate block = temp.start;
                    block.coords[i] = j;
                    blocks.push_back(block);
                }
            }
        }

        blocks.push_back(temp.end);

        bricks.push_back({blocks});
    }

    std::vector<Brick> dropped = dropAllBricks(bricks).first;

    int part1(0);
    int part2(0);

    for (int i = 0; i < dropped.size(); i++){
        std::vector<Brick> without = dropped;
        without.erase(without.begin() + i);
        int fellCount = dropAllBricks(without).second;
        if (fellCount == 0)
            part1++;
        part2 += fellCount;
    }

    std::cout << "Part01: " << part1 << std::endl;
    std::cout << "Part02: " << part2 << std::endl;

    return 0;
}
