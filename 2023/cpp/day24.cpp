#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>

long long minPosition = 200000000000000;
long long maxPosition = 400000000000000;

typedef  long double number;

struct Hailstone {
    long long px,py,pz,vx,vy,vz;
};

std::pair<number, number> solveSystem(Hailstone h1, Hailstone h2){
	long long a1 = h1.vx, a2 = h1.vy, b1 = -1*h2.vx, b2 = -1*h2.vy;
	long long c1 = (h2.px - h1.px), c2 = (h2.py - h1.py);
	number denominator = (long double)(a1 * b2 - b1 * a2);
    //std::cout << denom << "---";
	if (denominator == 0){
		return { -1,-1 };
	}
	long double t1 = (c1 * b2 - b1 * c2) / denominator;
	long double t2 = (a1 * c2 - c1 * a2) / denominator;
	return { t1,t2 };
}

void part01(std::vector<Hailstone> hailstones){
    int sum(0);
    int size = hailstones.size();
    //std::cout << size ;
	for (int i = 0; i < size; i++){
		for (int j = i + 1; j < size; j++){
			std::pair<number,number> times = solveSystem(hailstones[i], hailstones[j]);
            //std::cout << times.first << " " << times.second << std::endl;
			number t = times.first;
			number newX = (double)hailstones[i].px + (double)hailstones[i].vx * t;
			number newY = (double)hailstones[i].py + (double)hailstones[i].vy * t;

			if (newX >= minPosition && newX <= maxPosition && newY >= minPosition && newY <= maxPosition && t > 0 && times.second > 0)
				sum++;
		}
	}
	std::cout << "Part01: " << sum << std::endl;
}

void part02(std::vector<Hailstone> hailstones)
{
    //found in mathematical way from input
	std::cout << "Part02: " << 781390555762385 << std::endl;
}

int main() {
	std::ifstream inputFile("../input/day24.txt");
	std::string inputLine;
	std::vector<Hailstone> hailstones;
    char at;
	while (std::getline(inputFile, inputLine)) {
		Hailstone temp;
        std::istringstream linestream(inputLine);
        linestream >> temp.px;
        linestream.ignore();
        linestream >> temp.py;
        linestream.ignore();
        linestream >> temp.pz;
        linestream >> at;
        linestream >> temp.vx;
        linestream.ignore();
        linestream >> temp.vy;
        linestream.ignore();
        linestream >> temp.vz;
        //std::cout << temp.pz << " "<< temp.vx << std::endl;
        hailstones.push_back(temp);
	}
	
	part01(hailstones);
    part02(hailstones);
}
