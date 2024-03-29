#pragma once
#include "../create_params.hpp"

namespace xtd {
  namespace forms {
    namespace native {
      class check_box {
      public:
        check_box() = delete;
         static int check_state(intptr_t control);
         static void check_state(intptr_t control, int check_state);
      };
    }
  }
}
