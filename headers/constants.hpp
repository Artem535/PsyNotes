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
} // namespace emotions

namespace noteDetails {
constexpr char body[] = "body";
constexpr char thoughts[] = "thoughts";
constexpr char behavior[] = "behavior";
constexpr char situation[] = "situation";
} // namespace noteDetails

namespace questionsLabels {
constexpr char body[] = "what you feel in body?";
constexpr char thoughts[] = "What are you think?";
constexpr char behavior[] = "Your behaviour?";
constexpr char situation[] = "Situations?";
} // namespace questionsLabels

namespace database {
constexpr short defaultNoteID = 0;
} // namespace database

} // namespace constants