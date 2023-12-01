#include <cctype>
#include <iostream>
#include <fstream>
#include <string>

int main() {
    int sum = 0;

    std::ifstream file("input");
    std::string line;
    while (std::getline(file, line)) {
        int line_value = 0;

        for (auto it = line.begin(); it != line.end(); ++it) {
            if (std::isdigit(static_cast<unsigned char>(*it))) {
                line_value += 10 * (*it - '0');
                break;
            }
        }

        for (auto it = line.rbegin(); it != line.rend(); ++it) {
            if (std::isdigit(static_cast<unsigned char>(*it))) {
                line_value += *it - '0';
                break;
            }
        }

        sum += line_value;
    }

    std::cout << "sum: " << sum << '\n';
}
