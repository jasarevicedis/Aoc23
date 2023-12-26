#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <sstream>

bool allZero(std::vector<int> numbers){
    for(int n:numbers)
        if(n !=0)
            return false;
    return true;
}

void part01(std::vector<std::string> inputLines) {
    int results(0);
    std::vector<std::vector<int>> extrapolation;
    for(std::string line:inputLines){
        extrapolation.clear();
        int number;
        std::vector<int> numbers;
        std::stringstream linestream(line);
        while(linestream >> number)
            numbers.push_back(number);
        std::vector<int> down;//lower row
        extrapolation.push_back(numbers);

        for(;;){
            down.clear();
            auto current = (extrapolation.back());
            int size = current.size();
            
            for(int i=0; i< size-1;i++){
                down.push_back(current[i+1] - current[i]);
            }
            extrapolation.push_back(down);
            if(allZero(down))
                break;
        }
        
        
        int size=extrapolation.size();
        for(int i=size-1;i >=0;i--){
            if(i==size-1)
                extrapolation.at(i).push_back(0);
            else {
                extrapolation.at(i).push_back(extrapolation.at(i).back() + extrapolation.at(i+1).back());
            }
        }
        results+=extrapolation.at(0).back();
    }
    std::cout << "Part 01: " << results << std::endl;
}


void part02(std::vector<std::string> inputLines) {
    int results(0);
    std::vector<std::vector<int>> extrapolation;
    for(std::string line:inputLines){
        extrapolation.clear();
        int number;
        std::vector<int> numbers;
        std::stringstream linestream(line);
        while(linestream >> number)
            numbers.push_back(number);
        std::vector<int> down;//lower row
        extrapolation.push_back(numbers);

        for(;;){
            down.clear();
            auto current = (extrapolation.back());
            int size = current.size();
            
            for(int i=0; i< size-1;i++){
                down.push_back(current[i+1] - current[i]);
            }
            extrapolation.push_back(down);
            if(allZero(down))
                break;
        }
        
        
        int size=extrapolation.size();
        for(int i=size-1;i >=0;i--){
            if(i==size-1)
                extrapolation.at(i).insert(extrapolation.at(i).begin(), 0);
            else {
                extrapolation.at(i).insert( extrapolation.at(i).begin(), extrapolation.at(i).front() - extrapolation.at(i+1).front());
            }
        }
        results+=extrapolation.at(0).front();
    }
    std::cout << "Part 02: " << results << std::endl;
}

int main() {
    std::ifstream inputFile("../input/day09.txt");
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
