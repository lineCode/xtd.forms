#include <xtd/forms/native/control.hpp>
#include <xtd/forms/native/panel.hpp>
#include <xtd/forms/native/window_styles.hpp>
#include "../../../include/xtd/forms/panel.hpp"

using namespace xtd;
using namespace xtd::forms;

panel::panel() {
  this->make_control(*this);
  this->control::data_->auto_size_mode_ = forms::auto_size_mode::grow_only;
  this->control::data_->size_ = this->default_size();
}

panel& panel::operator=(const panel& value) {
  this->control::operator=(value);
  this->data_ = value.data_;
  return *this;
}

panel& panel::auto_size_mode(forms::auto_size_mode value) {
  this->set_auto_size_mode(value);
  return *this;
}

panel& panel::border_style(forms::border_style border_style) {
  if (this->data_->border_style_ != border_style) {
    this->data_->border_style_ = border_style;
    this->recreate_handle();
  }
  return *this;
}

forms::create_params panel::create_params() const {
  forms::create_params create_params = this->control::create_params();
  
  create_params.class_name("panel");
  create_params.style(create_params.style() | WS_CLIPSIBLINGS);
  
  if (this->data_->border_style_ == forms::border_style::fixed_single) create_params.style(create_params.style() | WS_BORDER);
  else if (this->data_->border_style_ == forms::border_style::fixed_3d) create_params.ex_style(create_params.ex_style() | WS_EX_CLIENTEDGE);
  
  return create_params;
}

drawing::size panel::measure_control() const {
  drawing::rectangle bounds;
  for (auto item : this->controls())
    bounds = drawing::rectangle::make_union(bounds, item.get().bounds());
  return drawing::size(bounds.location() + bounds.size());
}
