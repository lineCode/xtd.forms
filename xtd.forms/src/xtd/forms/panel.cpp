#include <xtd/forms/native/control.hpp>
#include <xtd/forms/native/panel.hpp>
#include "../../../include/xtd/forms/panel.hpp"

using namespace xtd;
using namespace xtd::forms;

void panel::border_style(forms::border_style border_style) {
  if (this->border_style_ != border_style) {
    this->border_style_ = border_style;
    this->recreate_handle();
  }
}

void panel::create_handle() {
  native::panel::styles styles = native::panel::styles::none;
  if (this->border_style_ == forms::border_style::fixed_single) styles += native::panel::styles::border_fixed_single;
  if (this->border_style_ == forms::border_style::fixed_3d) styles += native::panel::styles::border_fixed_3d;
  this->handle_ = native::panel::create(this->parent_->__get_handle__(), this->default_size(), styles);
  this->control::create_handle();
}
