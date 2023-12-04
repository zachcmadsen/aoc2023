#include <charconv>
#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include <unordered_set>

constexpr auto to_sv = std::views::transform([](auto &&range)
                                             { return std::string_view{&*std::ranges::begin(range), static_cast<std::size_t>(std::ranges::distance(range))}; });

constexpr auto split_str(const auto &c)
{
    return std::views::split(c) | to_sv;
}

int main()
{
    std::ifstream input_file{"input"};
    std::string input = {std::istreambuf_iterator{input_file}, {}};

    int card_value_total = 0;
    std::unordered_set<int> winning_numbers_set;

    for (std::string_view line : input | split_str('\n'))
    {
        // Remove the card number prefix and the space after it.
        line.remove_prefix(line.find(':') + 2);

        std::size_t pipe_pos = line.find('|');
        // Exclude the pipe from both substrings.
        std::string_view winning_numbers_str = line.substr(0, pipe_pos - 1);
        std::string_view numbers_str = line.substr(pipe_pos + 1);

        for (std::string_view winning_number_str : winning_numbers_str | split_str(' '))
        {
            int winning_number = std::stoi(winning_number_str.data());
            winning_numbers_set.insert(winning_number);
        }

        int card_value = 0;
        for (std::string_view number_str : numbers_str | split_str(' '))
        {
            if (number_str.empty())
            {
                continue;
            }

            int number;
            std::from_chars(number_str.begin(), number_str.end(), number);
            if (winning_numbers_set.contains(number))
            {
                card_value = card_value == 0 ? 1 : card_value * 2;
            }
        }

        card_value_total += card_value;
        winning_numbers_set.clear();
    }

    std::cout << "part 1: " << card_value_total << '\n';
}
