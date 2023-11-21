#pragma once
#include <array>
#include <database.obx.hpp>
#include <map>
#include <string_view>

namespace constants {

namespace emotions {
constexpr char emotAngry[] = "ANGRY";
constexpr char emotFear[] = "FEAR";
constexpr char emotSad[] = "SAD";
constexpr char emotHappy[] = "HAPPY";
constexpr char emotLove[] = "LOVE";
constexpr std::array<std::string_view, 5> emotList = {
    emotAngry, emotFear, emotHappy, emotLove, emotSad};
} // namespace emotions

namespace questionsLabels {
constexpr char body[] = "what you feel in body?";
constexpr char thoughts[] = "What are you think?";
constexpr char behavior[] = "Your behaviour?";
constexpr char situation[] = "Situations?";
}; // namespace questionsLabels

namespace database {
constexpr short defaultNoteID = 0;
}

} // namespace constants
