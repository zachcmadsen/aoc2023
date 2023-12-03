#include <charconv>
#include <fstream>
#include <iostream>
#include <ranges>

constexpr auto to_sv = std::views::transform([](auto &&range)
                                             { return std::string_view{&*std::ranges::begin(range), static_cast<std::size_t>(std::ranges::distance(range))}; });

constexpr auto split_str(const auto &c)
{
    return std::views::split(c) | to_sv;
}

int main()
{
    const int actual_red = 12;
    const int actual_green = 13;
    const int actual_blue = 14;

    int possible_game_sum = 0;
    int power_sum = 0;

    std::ifstream input_file{"input"};
    std::string input = {std::istreambuf_iterator{input_file}, {}};

    for (auto &&[game_num, line] : input | split_str('\n') | std::views::enumerate)
    {
        // Remove the game number since it's already tracked by the loop.
        line.remove_prefix(line.find(':') + 2);

        int min_red = 0;
        int min_green = 0;
        int min_blue = 0;

        for (std::string_view round : line | split_str(';'))
        {
            // Remove a leading space if it has one.
            if (round.front() == ' ')
            {
                round.remove_prefix(1);
            }

            for (auto &&count_color_pair : round | split_str(' ') | std::views::chunk(2))
            {
                auto it = std::ranges::begin(count_color_pair);
                std::string_view count_str = *it;
                std::string_view color = *std::next(it);

                int count;
                std::from_chars(count_str.data(), count_str.data() + count_str.size(), count);

                if (color.front() == 'r')
                {
                    min_red = std::max(min_red, count);
                }
                else if (color.front() == 'g')
                {
                    min_green = std::max(min_green, count);
                }
                else if (color.front() == 'b')
                {
                    min_blue = std::max(min_blue, count);
                }
            }
        }

        if (min_red <= actual_red && min_green <= actual_green && min_blue <= actual_blue)
        {
            // game_num is zero indexed.
            possible_game_sum += game_num + 1;
        }

        power_sum += min_red * min_green * min_blue;
    }

    std::cout << "part 1: " << possible_game_sum << '\n';
    std::cout << "part 2: " << power_sum << '\n';
}
