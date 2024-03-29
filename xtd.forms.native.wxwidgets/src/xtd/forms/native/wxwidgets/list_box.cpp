#include <stdexcept>
#include <xtd/drawing/system_colors.hpp>
#include <xtd/forms/native/application.hpp>
#include <xtd/forms/native/list_box.hpp>
#include "wx_list_box.hpp"

using namespace std;
using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms::native;

color list_box::default_back_color() {
#if wxMAJOR_VERSION >= 3 && wxMINOR_VERSION >= 1
  return system_colors::window();
#else
  static color default_color;
  if (default_color == color::empty) {
    native::application::start_application();
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "");
    wxListBox* list_box = new wxListBox(frame, wxID_ANY);
    wxColour colour = list_box->GetBackgroundColour();
#if defined (__WXOSX__)
    default_color = color::from_handle(reinterpret_cast<intptr_t>(colour.OSXGetNSColor()));
#else
    default_color = color::from_argb(colour.Alpha(), colour.Red(), colour.Green(), colour.Blue());
#endif
    delete list_box;
    delete frame;
  }
  return default_color;
#endif
}

color list_box::default_fore_color() {
#if wxMAJOR_VERSION >= 3 && wxMINOR_VERSION >= 1
  return system_colors::window_text();
#else
  static color default_color;
  if (default_color == color::empty) {
    native::application::start_application();
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "");
    wxListBox* list_box = new wxListBox(frame, wxID_ANY);
    wxColour colour = list_box->GetForegroundColour();
#if defined (__WXOSX__)
    default_color = color::from_handle(reinterpret_cast<intptr_t>(colour.OSXGetNSColor()));
#else
    default_color = color::from_argb(colour.Alpha(), colour.Red(), colour.Green(), colour.Blue());
#endif
    delete list_box;
    delete frame;
  }
  return default_color;
#endif
}

void list_box::delete_item(intptr_t control, size_t index) {
  if (control == 0) return;
  static_cast<wxListBox*>(reinterpret_cast<control_handler*>(control)->control())->Delete(index);
}

size_t list_box::insert_item(intptr_t control, size_t index, const string& item) {
  if (control == 0) return -1;
  if (!static_cast<wxListBox*>(reinterpret_cast<control_handler*>(control)->control())->IsSorted())
    return static_cast<wxListBox*>(reinterpret_cast<control_handler*>(control)->control())->Insert(item, index);
  return static_cast<wxListBox*>(reinterpret_cast<control_handler*>(control)->control())->Append(item);
}

size_t list_box::selected_index(intptr_t control) {
  if (control == 0) return -1;
  if (static_cast<wxListBox*>(reinterpret_cast<control_handler*>(control)->control())->HasMultipleSelection()) {
    vector<size_t> indices = selected_indices(control);
    if (indices.empty()) return -1;
    return indices[0];
  }
  return static_cast<wxListBox*>(reinterpret_cast<control_handler*>(control)->control())->GetSelection();
}

void list_box::selected_index(intptr_t control, size_t index) {
  if (control == 0) return;
  return static_cast<wxListBox*>(reinterpret_cast<control_handler*>(control)->control())->SetSelection(index);
}

vector<size_t> list_box::selected_indices(intptr_t control) {
  if (control == 0) return {};
  vector<size_t> indices;
  wxArrayInt wx_indices;
  static_cast<wxListBox*>(reinterpret_cast<control_handler*>(control)->control())->GetSelections(wx_indices);
  for (int index : wx_indices)
    indices.push_back(index);
  return indices;
    
}
