#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>



std::vector<int> add(std::vector<int> v1, std::vector<int> v2){
	std::vector<int> sum;
	for (int i = 0; i < v1.size(); i++)
		sum.push_back(v1[i] + v2[i]);
	return sum;
}

std::vector<int> simulatePulses(std::queue<std::string> locations, std::queue<int> pulseTypes, std::vector<std::string> modules, std::vector<int> types,std::vector<std::vector<std::string>>links,std::vector<std::string>flipFlops,std::vector<bool>&flipFlopStatus,std::vector<std::string> conjunctions, std::vector<std::vector<std::string>>conjunctionInputs, std::vector<std::vector<int>>&conjunctionPrevs,std::queue<std::string>prev, int iterNum=0){
	std::vector<int> total = { 1,0,0};
	int iter = 0;
	std::vector<int> numRxPushes = { 0,0 };
	while (locations.size() > 0){
		iter++;
		std::string current = locations.front();
		locations.pop();
		int pulseType = pulseTypes.front();
		pulseTypes.pop();
		std::string previous = prev.front();
		prev.pop();
		int index = find(modules.begin(), modules.end(), current) - modules.begin();

		if (current == "rx")
			numRxPushes[pulseType]++;

		if(index>=0&&index< modules.size()){
			int type = types[index];
			if (type == 0){
				for (int j = 0; j < links[index].size(); j++){
					
					total[0]++;
					locations.push(links[index][j]);
					pulseTypes.push(0);
					prev.push(current);
					int newIndex = find(modules.begin(), modules.end(), links[index][j]) - modules.begin();
				}
			}
			if (type == 1){
				int fIndex = find(flipFlops.begin(), flipFlops.end(), current) - flipFlops.begin();
				if (pulseType == 0){
					bool newStatus = !flipFlopStatus[fIndex];
					flipFlopStatus[fIndex] = newStatus;
					for (int j = 0; j < links[index].size(); j++){
						total[newStatus]++;
						locations.push(links[index][j]);
						pulseTypes.push(newStatus);
						prev.push(current);
						
						int newIndex = find(modules.begin(), modules.end(), links[index][j]) - modules.begin();
					}
				}
			}
			if (type == 2){
				int cIndex = find(conjunctions.begin(), conjunctions.end(), current) - conjunctions.begin();
				conjunctionPrevs[cIndex][find(conjunctionInputs[cIndex].begin(), conjunctionInputs[cIndex].end(), previous) - conjunctionInputs[cIndex].begin()] = pulseType;
				int conjTotal = 0;
				for (int i = 0; i < conjunctionPrevs[cIndex].size(); i++)
					conjTotal += conjunctionPrevs[cIndex][i];
				bool sendPulseType = 1;
				if(conjTotal == conjunctionPrevs[cIndex].size())
					sendPulseType = 0;
				
				for (int j = 0; j < links[index].size(); j++){
					total[sendPulseType]++;
					locations.push(links[index][j]);
					pulseTypes.push(sendPulseType);
					prev.push(current);
					
				}
			}
		}
	}
	std::vector<int> winner = { 1,0 };
	
	if (numRxPushes == winner)
	{
		total[2] = 1;
	}
	return total;
}



int main() {
	std::ifstream inputFile("../input/day20.txt");
	int totalCount = 0;
	std::string inputLine;
	std::vector<std::string> modules;
	std::vector<int> types;
	std::vector<std::vector<std::string>>links;
	std::vector<std::string> flipFlops;
	std::vector<bool> flipFlopStatus;
	std::vector<std::string> conjunctions;
	std::vector<std::vector<std::string>>conjunctionInputs;
	std::vector<std::vector<int>>conjunctionPrevs;

	while (getline(inputFile, inputLine)) {
		char type = inputLine[0];
		int pos = inputLine.find('>')+2;
		if (type == 'b'){
			modules.push_back("broadcaster");
			types.push_back(0);
			
		}
		else if (type == '%'){
			int space = inputLine.find(' ');
			std::string name = inputLine.substr(1, space - 1);
			modules.push_back(name);
			types.push_back(1);
			flipFlops.push_back(name);
			flipFlopStatus.push_back(false);
		}
		else if (type == '&'){
			int space = inputLine.find(' ');
			std::string name = inputLine.substr(1, space - 1);
			modules.push_back(name);
			types.push_back(2);
			conjunctions.push_back(name);
		}
		int comma = 0;
		std::vector<std::string>temp;
		while (comma != -1){
			comma = inputLine.find(',', pos);
			temp.push_back(inputLine.substr(pos, comma - pos));
			pos = comma + 2;
		}
		links.push_back(temp);
	}
	for (int i = 0; i < conjunctions.size(); i++){
		std::vector<std::string> temp;
		std::vector<int> temp2;
		for (int j = 0; j < modules.size(); j++)
		{	
			if (find(links[j].begin(), links[j].end(), conjunctions[i]) != links[j].end())
			{
				temp.push_back(modules[j]);
				temp2.push_back(0);
			}
			
		}
		conjunctionInputs.push_back(temp);
		conjunctionPrevs.push_back(temp2);
	}

	std::string start = "broadcaster";
	int pulse = 0;
	std::string button = "button";
	std::vector<int> total = { 0,0 };
	std::queue<std::string>locations;
	std::queue<int>pulses;
	std::queue<std::string>prev;
	locations.push(start);
	pulses.push(pulse);
	prev.push(button);

	for (int i = 0; i < 1000; i++){	
		std::vector<int> currentRun = simulatePulses(locations, pulses, modules, types, links, flipFlops, flipFlopStatus, conjunctions, conjunctionInputs, conjunctionPrevs, prev);
		total = add(total, currentRun);
	}
	
	totalCount = total[0] * total[1];
	std::cout << "Part01: " << totalCount << std::endl;
	int iter = 0;
	for(;;){
		iter++;
		std::vector<int> currentRun = simulatePulses(locations, pulses, modules, types, links, flipFlops, flipFlopStatus, conjunctions, conjunctionInputs, conjunctionPrevs, prev,iter);
		if (currentRun[2] == 1){
			std::cout << "Part02: " << iter+ 1 << std::endl;
			break;
		}
	}
}



