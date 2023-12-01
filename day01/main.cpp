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

        for (int i = 0; i < line.size(); ++i) {
            auto c = line[i];
            if (std::isdigit(static_cast<unsigned char>(c))) {
                line_value += 10 * (c - '0');
                break;
            }
        }

        for (int i = line.size() - 1; i >= 0; --i) {
            auto c = line[i];
            if (std::isdigit(static_cast<unsigned char>(c))) {
                line_value += c - '0';
                break;
            }
        }

        sum += line_value;
    }

    std::cout << "sum: " << sum << '\n';
}
