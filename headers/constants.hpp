#pragma once
#include <array>
#include <map>
#include <string_view>

namespace constants {

namespace emotions {
constexpr char kEmotAngry[] = "ANGRY";
constexpr char kEmotFear[] = "FEAR";
constexpr char kEmotSad[] = "SAD";
constexpr char kEmotHappy[] = "HAPPY";
constexpr char kEmotLove[] = "LOVE";
} // namespace emotions

namespace noteDetails {
constexpr char kBody[] = "body";
constexpr char kThoughts[] = "thoughts";
constexpr char kBehavior[] = "behavior";
constexpr char kSituation[] = "situation";
} // namespace noteDetails

namespace questionsLabels {
constexpr char kBody[] = "what you feel in body?";
constexpr char kThoughts[] = "What are you think?";
constexpr char kBehavior[] = "Your behaviour?";
constexpr char kSituation[] = "Situations?";
} // namespace questionsLabels

namespace database {
constexpr short kDefaultNoteID = 0;
constexpr char kDatabaseName[] = "notestorage.db";
} // namespace database

} // namespace constants
