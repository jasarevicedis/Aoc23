#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <queue>


typedef long long int  number;
std::vector<std::vector<number>> shifts = { {0, -1}, {1,0}, {0,1},{-1,0} };

std::vector<number> add(std::vector<number> v1, std::vector<number> v2){
	std::vector<number> sum;
	for (number i = 0; i < v1.size(); i++)
		sum.push_back(v1[i] + v2[i]);
	return sum;
}

bool isInside(std::vector<number> coords, number heigth, number width){
	number x = coords[0];
    number y = coords[1];
	if (x >= 0 && x < heigth && y >= 0 && y < width)
		return true;
	return false;
}

bool isDigit(char c){
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

std::vector<number> stringToNumber(std::string line, number pos = 0){
	std::vector<number> num;
	number space = 0;
	while (space != -1){
		space = line.find(' ', pos);
		num.push_back(stoi(line.substr(pos, -1)));
		pos = space + 1;
	}
	return num;
}

std::queue<std::vector<number>> setToQueue(std::set<std::vector<number>> input){
	std::queue<std::vector<number>>num;
	for (auto it = input.begin(); it != input.end(); ++it)
		num.push(*it);
	return num;
}

number sumGrid(std::vector<std::string> grid, char toCount){
	number num = 0;
	for (number i = 0; i < grid.size(); i++)
		for (number j = 0; j < grid[i].size(); j++)
			if (grid[i][j] == toCount)
				num++;
	return num;
}



number polynomial(number x, std::vector<number>polynomialCoefficients){
	//INTERPOLACIJA
    //NUMERICKI ALGORITMI <3
	number total = 0;
	for (number i = 0; i < polynomialCoefficients.size(); i++){
		long long temp = polynomialCoefficients[i];
		for (number j = 0; j < polynomialCoefficients.size(); j++){
			if (j != i)
				temp *= (long long)(x - j - 1) / (i - j);
		}
		total += temp;
	}
	return total;
}

void part01(std::vector<std::string> grid,std::queue<std::vector<number>> positions,std::set<std::vector<number>> nextPositions){
    number totalSteps = 64;
	number height = grid.size();
	number width = grid[0].size();

	std::vector<number> startPoint = positions.front();
	std::vector<std::string> startGrid = grid;

	for (number i = 0; i < totalSteps; i++){
		while (positions.size() > 0){
			std::vector<number> current = positions.front();
			positions.pop();
			number x = current[0], y = current[1];
			grid[y][x] = '.';
			for (number j = 0; j < 4; j++){
				std::vector<number> nextPos = add(current, shifts[j]);
				if (isInside(nextPos, width, height) && grid[nextPos[1]][nextPos[0]] != '#'){
					nextPositions.insert(nextPos);
					grid[nextPos[1]][nextPos[0]] = 'O';
				}
			}
		}
		positions = setToQueue(nextPositions);
		nextPositions.clear();
	}


	number totalCount = sumGrid(grid, 'O');
	std::cout << "Part01: " << totalCount << std::endl;
}
void part02(std::vector<std::string> grid,std::queue<std::vector<number>> positions,std::set<std::vector<number>> nextPositions){
    number totalSteps = 64;
	number height = grid.size();
	number width = grid[0].size();
    positions = std::queue<std::vector<number>>();
    std::vector<number> startPoint = positions.front();
	positions.push(startPoint);
	std::vector<number>polynomialCoeffs;

	totalSteps = width * 3;
	for (number i = 0; i < totalSteps; i++){
		while (positions.size() > 0){
			std::vector<number> current = positions.front();
			positions.pop();
			for (number j = 0; j < 4; j++){
				std::vector<number> nextPos = add(current, shifts[j]);
				number x = nextPos[0] % width, y = nextPos[1] % height;
				if (x < 0) { x += width; }
				if (y < 0) { y += height; }
				if (grid[y][x] != '#')
					nextPositions.insert(nextPos);
			}
		}
		positions = setToQueue(nextPositions);
		nextPositions.clear();

		number iter = i - (width / 2 - 1);
		if (iter % width == 0)
			polynomialCoeffs.push_back(positions.size());
	}
	
	number totalIterations = 26501365;
	number xToFind = (totalIterations - (width/2)) / width;

	long long total = polynomial(xToFind+1, polynomialCoeffs); 
	std::cout << "Part02: " << total << std::endl;
}

int main() {
	std::ifstream inputFile("../input/day21.txt");
	std::string lineN;
	std::vector<std::string> grid;
	std::queue<std::vector<number>> positions;
	std::set<std::vector<number>> nextPositions;
	std::vector<number>nums;
	number lineNum = 0;
	while (getline(inputFile, lineN)) {
		grid.push_back(lineN);
		number s = lineN.find('S');
		if (s != -1)
		{
			positions.push({ s,lineNum });
			grid[lineNum][s] = '.';
		}
		lineNum++;
	}
	part01(grid,positions,nextPositions);
    part02(grid, positions, nextPositions);

	return 0;
}
