#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

typedef struct lists {
    std::vector<int> leftList;
    std::vector<int> rightList;
} lists;

std::ifstream openFile(const std::string &fileName) {
    std::ifstream file;
    file.open(fileName, std::ifstream::in);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << fileName << std::endl;
        throw std::runtime_error("Error opening file");
    }

    return file;
}

lists readLists(std::ifstream &file) {
    lists locationLists;

    int leftNumber = 0, rightNumber = 0;

    while (file >> leftNumber >> rightNumber) {
        locationLists.leftList.push_back(leftNumber);
        locationLists.rightList.push_back(rightNumber);
    }

    return locationLists;
}

void sortLists(lists &locationLists) {
    std::sort(locationLists.leftList.begin(), locationLists.leftList.end());
    std::sort(locationLists.rightList.begin(), locationLists.rightList.end());
}

int calculateDistances(const lists &locationList) {
    int totalDistance = 0;

    for (int i = 0; i < locationList.leftList.size(); i++) {
        totalDistance += std::abs(locationList.rightList[i] - locationList.leftList[i]);
    }

    return totalDistance;
}

int main() {
    std::ifstream file = openFile("../input.txt");

    lists locationList = readLists(file);

    sortLists(locationList);

    std::cout << calculateDistances(locationList) << std::endl;

    file.close();
    return 0;
}
