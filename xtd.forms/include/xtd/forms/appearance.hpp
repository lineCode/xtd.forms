#pragma once
#include <xtd/xtd.strings>

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::forms namespace contains classes for creating Windows-based applications that take full advantage of the rich user interface features available in the Microsoft Windows operating system, Apple macOS and Linux like Ubuntu operating system.
  namespace forms {
    /// @brief Specifies the appearance of a control.
    /// @remarks Use the members of this enumeration in controls that provide the Appearance property to set its value.
    enum class appearance {
      /// @brief The default appearance defined by the control class.
      normal = 0,
      /// @brief The appearance of a Windows button.
      button = 1,
    };

    /// @cond
    inline std::ostream& operator<<(std::ostream& os, appearance value) {return os << to_string(value, {{appearance::normal, "normal"}, {appearance::button, "button"}});}
    inline std::wostream& operator<<(std::wostream& os, appearance value) {return os << to_string(value, {{appearance::normal, L"normal"}, {appearance::button, L"button"}});}
    /// @endcond
  }
}
