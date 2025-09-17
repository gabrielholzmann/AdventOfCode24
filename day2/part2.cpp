#include <cstring>
#include <iostream>
#include <vector>

typedef std::vector<int> Report;

typedef struct ReportLists {
    std::vector<Report> reportLists;
} ReportLists;

FILE *openFile(const char *filename) {
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        throw std::runtime_error("Could not open file");
    }

    return fp;
}

ReportLists readReportLists(FILE *fp) {
    ReportLists rl;
    char line[50];

    while (fgets(line, 50, fp)) {
        Report r;

        char *ptr = strtok(line, " ");
        while (ptr) {
            r.push_back(atoi(ptr));
            ptr = strtok(nullptr, " ");
        }

        rl.reportLists.push_back(r);
    }
    return rl;
}

bool checkIfReportIsValid(const Report &r) {
    int modifier = (r[0] > r[1]) ? 1 : -1;

    for (int i = 0; i < r.size() - 1; ++i) {
        int diff = (r[i] - r[i + 1]) * modifier;

        if (diff < 1 || diff > 3)
            return false;
    }
    return true;
}

bool checkIfReportIsValidByRemovingOne(const Report &r) {
    if (checkIfReportIsValid(r))
        return true;

    for (int i = 0; i < r.size(); ++i) {
        Report temp = r;
        temp.erase(temp.begin() + i);
        if (checkIfReportIsValid(temp))
            return true;
    }
    return false;
}

int calculateValidReportsTotal(ReportLists &rl) {
    int totalValid = 0;

    for (auto &r : rl.reportLists) {
        totalValid += checkIfReportIsValidByRemovingOne(r);
    }

    return totalValid;
}

int main() {
    FILE *fp = openFile("../input.txt");

    ReportLists rl = readReportLists(fp);

    std::cout << calculateValidReportsTotal(rl) << std::endl;

    return 0;
}
