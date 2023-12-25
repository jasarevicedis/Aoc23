#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//these 4 could be as one function
void tiltUp(std::vector<std::vector<char>> &mat) {
    int rowNum=mat.size();
    int colNum = mat[0].size();
    for(int i=0;i<rowNum;i++){
        for(int j=0;j<colNum;j++){
            if(mat[i][j] == 'O'){
                int k=i;
                while(k>0 && mat[k-1][j]!='O' && mat[k-1][j] != '#'){
                    char tmp = mat[k-1][j];
                    mat[k-1][j]=mat[k][j];
                    mat[k][j]=tmp;
                    k--;
                }
            }
        }
    }
}
void tiltLeft(std::vector<std::vector<char>> &mat) {
    int rowNum=mat.size();
    int colNum = mat[0].size();
    for(int i=0;i<rowNum;i++){
        for(int j=0;j<colNum;j++){
            if(mat[i][j] == 'O'){
                int k=j;
                while(k>0 && mat[i][k-1]!='O' && mat[i][k-1] != '#'){
                    char tmp = mat[i][k-1];
                    mat[i][k-1]=mat[i][k];
                    mat[i][k]=tmp;
                    k--;
                }
            }
        }
    }
}
void tiltDown(std::vector<std::vector<char>> &mat) {
    int rowNum=mat.size();
    int colNum = mat[0].size();
    for(int i=rowNum-1;i>=0;i--){
        for(int j=0;j<colNum;j++){
            if(mat[i][j] == 'O'){
                int k=i;
                while(k<rowNum-1 && mat[k+1][j]!='O' && mat[k+1][j] != '#'){
                    char tmp = mat[k+1][j];
                    mat[k+1][j]=mat[k][j];
                    mat[k][j]=tmp;
                    k++;
                }
            }
        }
    }
}
void tiltRight(std::vector<std::vector<char>> &mat) {
    int rowNum=mat.size();
    int colNum = mat[0].size();
    for(int i=0;i<rowNum;i++){
        for(int j=colNum-1;j>=0;j--){
            if(mat[i][j] == 'O'){
                int k=j;
                while(k<colNum-1 && mat[i][k+1]!='O' && mat[i][k+1] != '#'){
                    char tmp = mat[i][k+1];
                    mat[i][k+1]=mat[i][k];
                    mat[i][k]=tmp;
                    k++;
                }
            }
        }
    }
}
int countLoad(std::vector<std::vector<char>> mat){
    int rowNum=mat.size();
    int colNum = mat[0].size();
    int load(0);
    for(int i=0;i<rowNum;i++){
        for(int j=0;j<colNum;j++){
            if(mat[i][j] == 'O'){
                load += rowNum-i;
            }
        }
    }
    return load;
}

void part01(std::vector<std::vector<char>> &mat) {
    int rowNum=mat.size();
    int colNum = mat[0].size();
    /*
    for(int i=0;i<rowNum;i++){
        for(int j=0;j<colNum;j++){
            std::cout << mat[i][j];
        }
        std::cout <<std::endl;
    }
    std::cout <<std::endl;*/
    tiltUp(mat);
    /*
    for(int i=0;i<rowNum;i++){
        for(int j=0;j<colNum;j++){
            std::cout << mat[i][j];
        }
        std::cout <<std::endl;
    }
    std::cout <<std::endl;*/
    int load = countLoad(mat);
    std::cout << "Part 01: " << load << std::endl;
}

void part02(std::vector<std::vector<char>> &mat) {
    
    //std::vector<std::vector<std::vector<char>>> matrice;
    int prev=countLoad(mat);
    int next=countLoad(mat);
    /*
    for(int i=0;i<2000;i++){
        tiltUp(mat);
        tiltLeft(mat);
        tiltDown(mat);
        tiltRight(mat);
        matrice.push_back(mat);
        std::cout  << std::find(matrice.begin(),matrice.end(), mat) - matrice.begin() << std::endl;
            
        prev=next;
        next=countLoad(mat);
        
        std::cout << countLoad(mat) << std::endl;
    }*/
    
//PREVIOUS LOOP SHOW US THAT CYCLES REPEAT 170-197

    prev=countLoad(mat);
    next=countLoad(mat);
    
    int loopModule = (1000000000-197)%27+197 -1 ;
    
    for(int i=0;i<loopModule;i++){
        tiltUp(mat);
        tiltLeft(mat);
        tiltDown(mat);
        tiltRight(mat);
        prev=next;
        next=countLoad(mat);
        //std::cout << next << std::endl;
    }
    std::cout << "Part 02: " << next << std::endl;

}

int main() {
  std::ifstream inputFile("../input/day14.txt");
  std::vector<std::vector<char>> inputLines;
  std::string inputLine;
  while (std::getline(inputFile, inputLine)) {
    inputLines.resize(inputLines.size() + 1);
    for (char c : inputLine)
      inputLines.back().push_back(c);
  }
  inputFile.close();
  std::vector<std::vector<char>> inputLines2=inputLines;//copy cause matrix is rolled to top

  part01(inputLines);
  part02(inputLines2);

  return 0;
}
