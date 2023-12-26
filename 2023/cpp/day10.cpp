#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>


char map[140][140];

struct Coordinate {
    int x,y;
};

char findNewDirection(int row, int col, char going) {
    char tile = map[row][col];
    switch (tile) {
    case '|':
        if (going == 'n')
            return 'n';
        else if (going == 's')
            return 's';
        break;
    case '-':
        if (going == 'w')
            return 'w';
        else if (going == 'e')
            return 'e';
        break;
    case 'L':
        if (going == 's')
            return 'e';
        else if (going == 'w')
            return 'n';
        break;
    case 'J':
        if (going == 'e')
            return 'n';
        else if (going == 's')
            return 'w';
        break;
    case '7':
        if (going == 'n')
            return 'w';
        else if (going == 'e')
            return 's';
        break;
    case 'F':
        if (going == 'n')
            return 'e';
        else if (going == 'w')
            return 's';
        break;
    }

    return '\0';
}

void moveTile(int &row, int &col, char going) {
    switch (going) {
    case 'n':
        row++;
        break;
    case 'e':
        col++;
        break;
    case 's':
        row--;
        break;
    case 'w':
        col--;
        break;
    }
}

char getModedTile(char tile) {
    switch (tile) {
    case '|':
        return 'V';
    case '-':
        return 'H';
    case 'L':
        return 'l';
    case 'J':
        return 'j';
    case '7':
        return 's';
    case 'F':
        return 'f';
    }
    return '\0';
}

char getStartType(int row, int col)
{
    char test_n = findNewDirection(row + 1, col, 'n');
    char test_e = findNewDirection(row, col + 1, 'e');
    char test_s = findNewDirection(row - 1, col, 's');
    char test_w = findNewDirection(row, col - 1, 'w');

    if (test_n && test_s) {
        return '|';
    } else if (test_e && test_w) {
        return '-';
    } else if (test_n && test_e) {
        return 'L';
    } else if (test_n && test_w) {
        return 'J';
    } else if (test_s && test_w) {
        return '7';
    } else if (test_s && test_e) {
        return 'F';
    }

    return '\0';
}

int main ()
{
    std::ifstream f("../input/day10.txt");
    
    
    Coordinate start;

    std::string line;
    int row = 139;

    while (getline(f, line)) {
        if (line.empty())
            break;

        int i = 0;
        for (auto c : line) {
            if (c == 'S') {
                start.x = row;
                start.y = i;
            }
            map[row][i++] = c;
        }

        row--;
    }

    
    
    int roww = start.x;
    int col = start.y;
    char start_type = getStartType(roww, col);

    char going;
    switch (start_type) {
    case '|':
    case 'L':
    case 'J':
        going = 'n';
        break;
    case '-':
    case '7':
        going = 'w';
        break;
    case 'F':
        going = 's';
        break;
    }

    moveTile(roww, col, going);     

    int count = 1;
    while (map[roww][col] != 'S') {
        count++;
        going = findNewDirection(roww, col, going);
        map[roww][col] = getModedTile(map[roww][col]);
        moveTile(roww, col, going);     
    }
    
    std::cout << "Part 01: " << count/2 << "\n";
    

    map[start.x][start.y] = getModedTile(start_type);
    bool countTile = false;
    int tiles = 0;
    for (int r = 0; r < 140; r++) {
        
        for (int c = 0; c < 140; c++) {
            if (map[r][c] == 'l') {
                countTile = !countTile;
                while (map[r][c + 1] == 'H')
                    c++;
                if (map[r][c + 1] == 'j') {
                    countTile = !countTile;
                }
                c++; 
            } else if (map[r][c] == 'f') {
                countTile = !countTile;
                while (map[r][c + 1] == 'H')
                    c++;
                if (map[r][c + 1] == 's') {
                    countTile = !countTile;
                }
                c++; 
            } else if (map[r][c] == 'V') {
                countTile = !countTile;
            } else if (countTile) {
                tiles++;
            }
        }
    }

    std::cout << "Part 02: " << tiles << "\n";
    

    return 0;
}
