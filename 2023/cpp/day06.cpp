#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>





void part01(std::vector<std::string> inputLines) {
    int timeValue,distanceValue;
    std::string name;// nebitno, samo da uzme textualni dio linije
    std::vector<int> times;
    std::vector<int> distances;

    std::string line =  inputLines.at(0);
    std::stringstream linestream1(line);
    std::getline(linestream1, name, ':');
    while(linestream1 >> timeValue)
        times.push_back(timeValue);
    line =  inputLines.at(1);
    std::stringstream linestream2(line);
    std::getline(linestream2, name, ':');
    while(linestream2 >> distanceValue)
        distances.push_back(distanceValue);
    int speed, traveledDistance,winCounter;
    std::vector<int> winsPerRace;
    for(int i=0;i< times.size();i++){
        winCounter=0;
        //j predstavlja vrijeme ubrzavanja
        for(int j=0;j<=times[i];j++){
            speed=j;
            traveledDistance = (times[i]-j)*speed;
            if(traveledDistance > distances[i])
                winCounter++;
        }
        winsPerRace.push_back(winCounter);
    }
    int result1(1);
    for(int wins: winsPerRace)
        result1*=wins;
    std::cout << "Part 01: " << result1 << std::endl;
   
}


void part02(std::vector<std::string> inputLines) {
    long int time = 59707878;
    long int distance = 430121812131276;//hard coded from input
    long int speed;
    long int traveledDistance;
    int winCounter(0);
    for(int j=0;j<=time;j++){ 
        speed =j;    
        traveledDistance = (time-j)*speed;
            if(traveledDistance > distance)
                winCounter++;
              
    }
    std::cout << "Part 02: " << winCounter << std::endl;
}

int main() {
    std::ifstream inputFile("../input/day06.txt");
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
