#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include <string>
#include <unordered_map>

void part1()
{
    int sum = 0;

    std::ifstream file("input");
    std::string line;
    while (std::getline(file, line))
    {
        int line_value = 0;

        auto is_digit = [](char c)
        { return std::isdigit(static_cast<unsigned char>(c)); };

        char first_digit = *std::ranges::find_if(line, is_digit);
        line_value += 10 * (first_digit - '0');

        char last_digit = *std::ranges::find_if(line | std::views::reverse, is_digit);
        line_value += (last_digit - '0');

        sum += line_value;
    }

    std::cout << "part 1: " << sum << '\n';
}

void part2()
{
    int sum = 0;

    std::regex num_regex("(one|two|three|four|five|six|seven|eight|nine|\\d)");
    std::regex rnum_regex("(eno|owt|eerht|ruof|evif|xis|neves|thgie|enin|\\d)");

    std::unordered_map<std::string, int> num_lut =
        {
            {"one", 1},
            {"two", 2},
            {"three", 3},
            {"four", 4},
            {"five", 5},
            {"six", 6},
            {"seven", 7},
            {"eight", 8},
            {"nine", 9},
            {"eno", 1},
            {"owt", 2},
            {"eerht", 3},
            {"ruof", 4},
            {"evif", 5},
            {"xis", 6},
            {"neves", 7},
            {"thgie", 8},
            {"enin", 9},
            {"1", 1},
            {"2", 2},
            {"3", 3},
            {"4", 4},
            {"5", 5},
            {"6", 6},
            {"7", 7},
            {"8", 8},
            {"9", 9}};

    std::ifstream file("input");
    std::string line;
    while (std::getline(file, line))
    {
        int line_value = 0;

        std::smatch first_match;
        std::regex_search(line.cbegin(), line.cend(), first_match, num_regex);
        std::string first_match_str = first_match.str();
        line_value += 10 * num_lut[first_match_str];

        std::match_results<std::string::const_reverse_iterator> last_match;
        auto rnum_it = std::regex_search(line.crbegin(), line.crend(), last_match, rnum_regex);
        std::string last_match_str = last_match.str();
        line_value += num_lut[last_match_str];

        sum += line_value;
    }

    std::cout << "part 2: " << sum << '\n';
}

int main()
{
    part1();
    part2();
}
