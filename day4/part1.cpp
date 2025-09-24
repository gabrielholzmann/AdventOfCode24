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

const std::vector<offset> directionOffsets {
    {0, -1},
    {0, 1},
    {1, 0},
    {-1, 0},
    {1, -1},
    {-1, -1},
    {1, 1},
    {-1, 1}
};

const std::vector<char> xmasCharMap {'M', 'A', 'S'};

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

bool checkDirection(const map &m, int x, int y, const offset &off) {
    for (const auto &c : xmasCharMap) {
        x += off.xOffset;
        y += off.yOffset;

        if (!validCoordinates(m, x, y) || m.xmasMap[y][x] != c) {
            return false;
        }
    }

    return true;
}

int checkForMS(const map &m, int x, int y) {
    int total = 0;

    for (auto &off : directionOffsets) {
        total += checkDirection(m, x, y, off);
    }

    return total;
}

int scanMap(const map &m) {
    int total = 0;

    for (int y = 0; y < m.height; y++) {
        for (int x = 0; x < m.width; x++) {
            if (m.xmasMap[y][x] == 'X') {
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