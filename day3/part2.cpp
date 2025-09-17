#include <iostream>
#include <vector>
#include <regex>
#include <fstream>

const auto regexExpression = std::regex (R"(do\(\)|don't\(\)|mul\((\d+),(\d+)\))");

typedef struct memory {
    std::vector<std::string> instructions{};
    bool isEnabled{true};
} memory;

std::fstream openFile(const std::string &fileName) {
    std::fstream fp;
    fp.open(fileName, std::ios::in);

    if (!fp.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    return fp;
}

memory readInstructions(std::fstream &fp) {
    memory m;

    std::string line;
    while (std::getline(fp, line)) {
        m.instructions.push_back(line);
    }

    return m;
}

int matchRegexLine(memory &m, std::string line) {
    int total = 0;
    std::smatch match;

    while (std::regex_search(line, match, regexExpression)) {
        std::string fullMatch = match.str(0);

        if (fullMatch == "do()") {
            m.isEnabled = true;
        }
        else if (fullMatch == "don't()") {
            m.isEnabled = false;
        }
        else if (m.isEnabled) {
            total += std::stoi(match.str(1)) * std::stoi(match.str(2));
        }

        line = match.suffix().str();
    }

    return total;
}

int evaluateMultiplyInstructions(memory &m) {
    int total = 0;

    for (const auto &line : m.instructions) {
        total += matchRegexLine(m, line);
    }

    return total;
}

int main() {
    std::fstream inputFile = openFile("../input.txt");

    memory m = readInstructions(inputFile);

    std::cout << evaluateMultiplyInstructions(m);

    return 0;
}
