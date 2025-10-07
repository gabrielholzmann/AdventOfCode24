#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

typedef struct manual {
    std::unordered_map<int, std::vector<int>> ordering;
    std::vector<std::vector<int>> pages;
} manual;

FILE *openFile(const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        throw std::runtime_error("File could not be opened");
    }

    return fp;
}

void readOrdering (manual &manual, FILE *fp) {
    char line[10];

    int page{};
    int order{};

    while (fgets(line, 10, fp)) {
        if (line[0] == '\n')
            break;

        sscanf(line, "%d|%d", &page, &order);

        manual.ordering[page].push_back(order);
    }
}

void readPages (manual &manual, FILE *fp) {
    char line[100];

    while (fgets(line, 100, fp)) {
        std::vector<int> page;
        int pageNumber{};

        char *ptr = strtok(line, ",");

        while (ptr) {
            sscanf(ptr, "%d", &pageNumber);
            page.push_back(pageNumber);

            ptr = strtok(nullptr, ",");
        }

        manual.pages.push_back(page);
    }
}

manual readManual (FILE *fp) {
    manual m;

    readOrdering(m, fp);
    readPages(m, fp);

    return m;
}

bool checkIfPageIsValid(const manual &m, const std::vector<int> &page) {
    for (int currentNumber = page.size() - 1; currentNumber >= 1; currentNumber--) {

        auto currentNumberOrdering = m.ordering.find(page[currentNumber]);
        if (currentNumberOrdering == m.ordering.end())
            continue;

        auto &mustComeAfter = currentNumberOrdering->second;

        for (int previousNumber = currentNumber - 1; previousNumber >= 0; previousNumber--) {
            if (std::find(mustComeAfter.begin(), mustComeAfter.end(), page[previousNumber]) != mustComeAfter.end()) {
                return false;
            }
        }
    }

    return true;
}

int scanManual (const manual &m) {
    int total = 0;

    for (const auto &page : m.pages) {
        if (checkIfPageIsValid(m, page)) {
            total += page[page.size() / 2];
        }
    }

    return total;
}

int main() {
    FILE *fp = fopen("../input.txt", "r");

    manual m = readManual(fp);

    std::cout << scanManual(m) << std::endl;

    return 0;
}