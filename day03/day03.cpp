#include <charconv>
#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>

constexpr auto to_sv = std::views::transform([](auto &&range)
                                             { return std::string_view{&*std::ranges::begin(range), static_cast<std::size_t>(std::ranges::distance(range))}; });

constexpr auto split_str(const auto &c)
{
    return std::views::split(c) | to_sv;
}

constexpr auto is_digit = [](char c)
{ return std::isdigit(static_cast<unsigned char>(c)); };

int main()
{
    std::ifstream input_file{"input"};
    std::string input = {std::istreambuf_iterator{input_file}, {}};

    // Add one since it's zero indexed.
    const int cols = input.find('\n') + 1;
    const int rows = input.size() / cols;

    const auto get = [&](int row, int col)
    {
        if (row < 0 || row >= rows || col < 0 || col >= (cols - 1))
        {
            return '.';
        }

        return input[cols * row + col];
    };

    const auto is_symbol = [&](int row, int col)
    {
        char c = get(row, col);
        return c != '.' && !is_digit(c);
    };

    const auto is_adjacent_to_symbol = [&](int row, int col)
    {
        return is_symbol(row - 1, col) ||
               is_symbol(row + 1, col) ||
               is_symbol(row, col - 1) ||
               is_symbol(row, col + 1) ||
               is_symbol(row - 1, col - 1) ||
               is_symbol(row - 1, col + 1) ||
               is_symbol(row + 1, col - 1) ||
               is_symbol(row + 1, col + 1);
    };

    std::regex num_regex("[1-9][0-9]*");

    int part_number_sum = 0;

    for (auto [row, line] : input | split_str('\n') | std::views::enumerate)
    {
        for (auto it = std::cregex_iterator(line.begin(), line.end(), num_regex); it != std::cregex_iterator(); ++it)
        {
            bool is_part_number = false;
            for (int col = it->position(); col < it->position() + it->length(); ++col)
            {
                is_part_number |= is_adjacent_to_symbol(row, col);
            }

            if (is_part_number)
            {
                int part_number = std::stoi(it->str());
                part_number_sum += part_number;
            }
        }
    }

    std::cout << "part 1: " << part_number_sum << '\n';
}
