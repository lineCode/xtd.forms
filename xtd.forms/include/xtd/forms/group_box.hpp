#pragma once
#include "control.hpp"
#include "border_style.hpp"

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::forms namespace contains classes for creating Windows-based applications that take full advantage of the rich user interface features available in the Microsoft Windows operating system, Apple macOS and Linux like Ubuntu operating system.
  namespace forms {
    class group_box : public control {
    public:
      group_box();

      /// @cond
      group_box(const group_box& value) = default;
      group_box& operator=(const group_box& value);
      /// @endcond

      virtual forms::auto_size_mode auto_size_mode() const {return this->control::data_->auto_size_mode_;}
      virtual group_box& auto_size_mode(forms::auto_size_mode value);
      
      drawing::size default_size() const override {return{200, 100};}
      
    protected:
      forms::create_params create_params() const override;
      
      drawing::size measure_control() const override;

    private:
      struct data {
      };
      
      std::shared_ptr<data> data_ = std::make_shared<data>();
    };
  }
}
