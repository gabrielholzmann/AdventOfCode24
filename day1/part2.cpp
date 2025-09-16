#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

typedef struct lists {
    std::vector<int> leftList;
    std::vector<int> rightList;
} lists;

typedef std::unordered_map<int, int> frequencyMap;

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

frequencyMap calculateFrequency(const lists &locationLists) {
    frequencyMap fm;

    for (const auto &locationNumber : locationLists.rightList) {
        fm[locationNumber] += 1;
    }

    return fm;
}

int calculateSimilarityScore(const lists &locationList, const frequencyMap &fm) {
    int similarityScore = 0;

    for (const auto &locationNumber : locationList.leftList) {
        if (auto iter = fm.find(locationNumber); iter != fm.end())
            similarityScore += locationNumber * iter->second;
    }

    return similarityScore;
}

int main() {
    std::ifstream file = openFile("../input.txt");

    lists locationList = readLists(file);

    frequencyMap fm = calculateFrequency(locationList);

    std::cout << calculateSimilarityScore(locationList, fm) << std::endl;

    file.close();
    return 0;
}
