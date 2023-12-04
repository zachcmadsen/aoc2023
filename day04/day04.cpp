#include <charconv>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
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

    std::unordered_set<int> winning_numbers_set;
    std::vector<int> card_matches;

    for (std::string_view line : input | split_str('\n'))
    {
        // Remove the card number prefix and the space after it.
        line.remove_prefix(line.find(':') + 2);

        std::size_t pipe_pos = line.find('|');
        // Exclude the pipe from both substrings.
        std::string_view winning_numbers_str = line.substr(0, pipe_pos - 1);
        std::string_view numbers_str = line.substr(pipe_pos + 1);

        for (std::string_view winning_number_sv : winning_numbers_str | split_str(' '))
        {
            int winning_number;
            std::from_chars(winning_number_sv.data(), winning_number_sv.data() + winning_number_sv.size(), winning_number);
            winning_numbers_set.insert(winning_number);
        }

        int matches = 0;
        for (std::string_view number_sv : numbers_str | split_str(' '))
        {
            if (number_sv.empty())
            {
                continue;
            }

            int number;
            std::from_chars(number_sv.data(), number_sv.data() + number_sv.size(), number);
            if (winning_numbers_set.contains(number))
            {
                ++matches;
            }
        }

        card_matches.push_back(matches);
        winning_numbers_set.clear();
    }

    // Part 1
    int total_points = 0;
    for (int matches : card_matches)
    {
        total_points += 1 << (matches - 1);
    }

    // Part 2
    std::vector<int> card_copies(card_matches.size(), 0);
    for (std::size_t i = 0; i < card_matches.size(); ++i)
    {
        int matches = card_matches[i];
        int copies = card_copies[i];
        for (std::size_t j = i + 1; j < (matches + i + 1); ++j)
        {
            card_copies[j] += 1 + copies;
        }
    }
    int total_copies = std::accumulate(card_copies.begin(), card_copies.end(), 0);
    int total_cards = card_matches.size() + total_copies;

    std::cout << "part 1: " << total_points << '\n';
    std::cout << "part 2: " << total_cards << '\n';
}
