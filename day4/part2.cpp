#include <iostream>
#include <fstream>
#include <vector>

typedef struct map {
    std::vector<std::string> xmasMap{};
    int height{};
    int width{};
} map;

typedef struct offset {
    int xOffset;
    int yOffset;
} offset;

std::fstream openFile(const std::string &fileName) {
    std::fstream fp;
    fp.open(fileName, std::ios::in);

    if (!fp.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    return fp;
}

map readMap(std::fstream &file) {
    map m;
    std::string line;

    while (std::getline(file, line)) {
        m.xmasMap.push_back(line);
    }

    m.width = m.xmasMap[0].size();
    m.height = m.xmasMap.size();

    return m;
}

bool validCoordinates(const map &m, int x, int y) {
    return (x >= 0 && y >= 0 && x < m.width && y < m.height);
}

bool checkDiagonal(const map &m, const offset &diagonalOne, const offset &diagonalTwo) {
    if (validCoordinates(m, diagonalOne.xOffset, diagonalOne.yOffset) && validCoordinates(m, diagonalTwo.xOffset, diagonalTwo.yOffset)) {
        char c1 = m.xmasMap[diagonalOne.yOffset][diagonalOne.xOffset];
        char c2 = m.xmasMap[diagonalTwo.yOffset][diagonalTwo.xOffset];

        return (c1 == 'S' && c2 == 'M' || c1 == 'M' && c2 == 'S');
    }

    return false;
}

bool checkForMS(const map &m, int x, int y) {
    return checkDiagonal(m, {x + 1, y + 1}, {x - 1, y - 1}) &&
        checkDiagonal(m, {x + 1, y - 1}, {x - 1, y + 1});
}

int scanMap(const map &m) {
    int total = 0;

    for (int y = 0; y < m.height; y++) {
        for (int x = 0; x < m.width; x++) {
            if (m.xmasMap[y][x] == 'A') {
                total += checkForMS(m, x, y);
            }
        }
    }

    return total;
}

int main() {
    std::fstream fp = openFile("../input.txt");

    map m = readMap(fp);

    std::cout << scanMap(m) << std::endl;

    fp.close();
    return 0;
}