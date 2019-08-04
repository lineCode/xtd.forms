#pragma once
#include <xtd/drawing/size.hpp>
#include <cstdint>

namespace xtd {
  namespace forms {
    namespace native {
      class radio_button {
      public:
        static intptr_t create(intptr_t parent, const drawing::size& size);
        static bool checked(intptr_t control);
        static void checked(intptr_t control, bool checked);
      };
    }
  }
}