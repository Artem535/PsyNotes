#pragma once
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

namespace database {
constexpr obx_id emptyNoteID = -1;
}

} // namespace constants
