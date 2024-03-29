#pragma once
#include <cstdint>
#include <vector>
#include <xtd/xtd.delegates>

namespace xtd {
  namespace forms {
    namespace native {
      class application {
      public:
        application() = delete;
        static bool allow_quit();
        static void do_events();
        static void do_idle();
        static void enable_visual_style();
        static void end_application();
        static void exit();
        static void start_application();
        static intptr_t main_form();
        static void main_form(intptr_t handle);
        static std::vector<intptr_t> open_forms();
        static void register_wnd_proc(const delegate<intptr_t(intptr_t, int32_t, intptr_t, intptr_t, intptr_t)>& wnd_proc);
        static void run();
      };
    }
  }
}
