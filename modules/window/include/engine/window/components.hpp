#pragma once
#include <EASTL/fixed_list.h>

namespace engine {

  namespace window {
    struct Opened {};
    struct Focused {};
  } // namespace window

  namespace window::phases {
    struct EventPollPre {};
    struct EventPoll {};
  } // namespace phases
}