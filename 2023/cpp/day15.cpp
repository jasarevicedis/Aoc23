#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>



int hashTheString(const std::string &value) {
    int sum(0);
    for (char c : value) {
        sum += c;
        sum *= 17;
        sum %= 256;
    }
    return sum;
}

void part01(std::vector<std::string>inputLines){
    int sum(0);
    for (int i = 0; i < inputLines.size(); i++)
		sum += hashTheString(inputLines[i]);
    std::cout << "Part01: " << sum << std::endl;
}

void part02(std::vector<std::string>inputLines,std::vector<std::vector<std::string>>boxes,std::vector<std::vector<int>>lenses){
    int sum(0);
    for (int i = 0; i < inputLines.size(); i++){
		sum += hashTheString(inputLines[i]);
		std::string line = inputLines[i];
		if (line.find('=') != -1){
			std::string label = line.substr(0, line.size() - 2);
			int hashed = hashTheString(label);
			int focalLength = line[line.size() - 1] - '0';
			std::vector<std::string>::iterator currentPos = find(boxes[hashed].begin(),boxes[hashed].end(),label);
			if (currentPos != boxes[hashed].end()){
				int index = currentPos - boxes[hashed].begin();
				boxes[hashed][index] = label;
				lenses[hashed][index] = focalLength;
			}
			else{
				boxes[hashed].push_back(label);
				lenses[hashed].push_back(focalLength);
			}
		}
		else{
			std::string label = line.substr(0, line.size() - 1);
			int hashed = hashTheString(label);
			std::vector<std::string>::iterator currentPos = find(boxes[hashed].begin(), boxes[hashed].end(), label);
			if (currentPos != boxes[hashed].end()){
				int index = currentPos - boxes[hashed].begin();
				for (int i = index + 1; i < boxes[hashed].size(); i++){
					boxes[hashed][i - 1] = boxes[hashed][i];
					lenses[hashed][i - 1] = lenses[hashed][i];
				}
				boxes[hashed].pop_back();
				lenses[hashed].pop_back();
			}
		}
	}

	sum=0;
	for (int i = 0; i < boxes.size(); i++)
		for (int j = 0; j < boxes[i].size(); j++)
			sum += (i + 1) * (j + 1) * lenses[i][j];
    std::cout << "Part02: " << sum;
}

int main() {
	std::ifstream inputFile("../input/day15.txt");

	int totalCount = 0;
	std::string inputLine;
	std::vector<std::string>inputLines;
	std::vector<std::vector<std::string>>boxes;
	boxes.resize(256);
	std::vector<std::vector<int>>lenses;
	lenses.resize(256);
	while (getline(inputFile, inputLine)) {
		int position = 0;
		while (position < inputLine.size()){
			int comma = inputLine.find(',', position);
			if (comma != -1){
				inputLines.push_back(inputLine.substr(position, comma - position));
				position = comma + 1;
			}
			else{
				inputLines.push_back(inputLine.substr(position, -1));
				position = inputLine.size();
			}
		}
	}
	
    part01(inputLines);
    part02(inputLines, boxes, lenses);
    return 0;
}
