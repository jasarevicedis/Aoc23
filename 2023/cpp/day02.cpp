#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>

#include <map>


//Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
//12 red cubes, 13 green cubes, and 14 blue cubes
std::map<std::string,int> availableColors ={
    {"red", 12}, {"green", 13}, {"blue", 14}
};

void part01(std::vector<std::string> inputLines) {
    int validGameCounter(0);
    int colorNumber;
    std::string colorString;
    for(std::string line: inputLines) {  
        std::stringstream linestream(line);
        std::string game;
        std::getline(linestream,  game, ':');
        int gameNumber;
        sscanf(game.c_str(), "Game %d", &gameNumber);//c_str da pretvori u pokazivac
        
        bool colorsInRange = true;
        while (!linestream.eof())
        {
            std::string colorSetString;
            std::getline(linestream,  colorSetString, ';');

            std::stringstream colorsStream(colorSetString);
            //std::cout << colorsStream.str() << std::endl;
            std::map<std::string, int> gameColors;
            while (!colorsStream.eof())
            {
                std::string colorSetItem;
                std::getline(colorsStream,  colorSetItem, ',');
                colorNumber=0;
                colorString="";
                std::stringstream colorStream(colorSetItem);
                colorStream >> colorNumber;
                colorStream >> colorString;
                if (!gameColors.count(colorString))
                    gameColors[colorString] = colorNumber;
                else
                    gameColors[colorString] += colorNumber;//sum needs to be less or equal to available
                
            }
            for (auto value : gameColors)
            {
                if (value.second > availableColors[value.first])
                {
                    colorsInRange = false;
                    break;
                }
            }
                
        }
        if (colorsInRange)
            validGameCounter += gameNumber;
    }

    std::cout << "Part01: " << validGameCounter << std::endl;
}



void part02(std::vector<std::string> inputLines) {
    
    int colorNumber;
    std::string colorString;
    int product;
    int powerSum(0);
    for(std::string line: inputLines) {  
        product=1;
        std::stringstream linestream(line);
        std::string game;
        std::getline(linestream,  game, ':');
        int gameNumber;
        sscanf(game.c_str(), "Game %d", &gameNumber);//c_str da pretvori u pokazivac
        
        std::map<std::string, int> gameColors;
        while (!linestream.eof())
        {
            std::string colorSetString;
            std::getline(linestream,  colorSetString, ';');

            std::stringstream colorsStream(colorSetString);
            //std::cout << colorsStream.str() << std::endl;
            
            while (!colorsStream.eof())
            {
                std::string colorSetItem;
                std::getline(colorsStream,  colorSetItem, ',');
                colorNumber=0;
                colorString="";
                std::stringstream colorStream(colorSetItem);
                colorStream >> colorNumber;
                colorStream >> colorString;
                if (!gameColors.count(colorString))
                    gameColors[colorString] = colorNumber;
                else {
                    if(gameColors[colorString] < colorNumber)
                        gameColors[colorString] = colorNumber;
                }
            }
            
                
        } 
        product=1;
        for (auto value : gameColors){
            product*=value.second;
        }
        powerSum += product;
    }

    std::cout << "Part02: " << powerSum << std::endl;
}


int main() {
    std::ifstream inputFile("../input/day02.txt");
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
