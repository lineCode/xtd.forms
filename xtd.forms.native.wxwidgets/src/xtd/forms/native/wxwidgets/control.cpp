#include <map>
#include <stdexcept>
#include <xtd/forms/native/control.hpp>
#include "control_handler.hpp"
#include <wx/control.h>

using namespace std;
using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms::native;

namespace {
  class wx_control : public control_handler {
  public:
    wx_control(wxWindow *parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0) {
      this->create<wxControl>(parent, id, pos, size, style);
    }
  };
}

intptr_t control::create(intptr_t parent, const drawing::size& size) {
  if (parent == 0) throw invalid_argument("parent can't be null");
  return reinterpret_cast<intptr_t>(new wx_control(((control_handler*)parent)->control(), wxID_ANY, wxDefaultPosition, {size.width(), size.height()}));
}

intptr_t control::def_wnd_proc(intptr_t control, intptr_t hwnd, int msg, intptr_t wparam, intptr_t lparam, intptr_t presult, intptr_t handle) {
  switch (msg) {
  case WM_GETTEXTLENGTH: return (reinterpret_cast<control_handler*>(hwnd))->control()->GetLabel().ToStdString().size(); break;
  case WM_GETTEXT: return strlen(strncpy(reinterpret_cast<char*>(lparam), reinterpret_cast<control_handler*>(hwnd)->control()->GetLabel().ToStdString().c_str(), wparam)); break;
  }
  if (handle != 0) return reinterpret_cast<control_handler*>(control)->call_def_wnd_proc(hwnd, msg, wparam, lparam, presult, handle);
  return 0;
}

void control::destroy(intptr_t control) {
  if (control == 0) return;
  if (reinterpret_cast<control_handler*>(control)->control() == 0) return;
  reinterpret_cast<control_handler*>(control)->control()->Destroy();
  del(control);
}

void control::del(intptr_t control) {
  if (control == 0) return;
  delete reinterpret_cast<class control_handler*>(control);
}

drawing::size control::client_size(intptr_t control) {
  if (control == 0) return {};
  wxSize size = reinterpret_cast<control_handler*>(control)->control()->GetClientSize();
  return {size.GetWidth(), size.GetHeight()};
}

void control::client_size(intptr_t control, const drawing::size& size) {
  if (control == 0) return;
  reinterpret_cast<control_handler*>(control)->control()->SetClientSize(size.width(), size.height());
}

bool control::enabled(intptr_t control) {
  if (control == 0) return false;
  return reinterpret_cast<control_handler*>(control)->control()->IsEnabled();
}

void control::enabled(intptr_t control, bool enabled) {
  if (control == 0) return;
  reinterpret_cast<control_handler*>(control)->control()->Enable(enabled);
}

intptr_t control::handle(intptr_t control) {
  if (control == 0) return 0;
  return reinterpret_cast<intptr_t>(reinterpret_cast<control_handler*>(control)->control()->GetHandle());
}

point control::location(intptr_t control) {
  if (control == 0) return {};
  wxPoint location = reinterpret_cast<control_handler*>(control)->control()->GetPosition();
  return {location.x, location.y};
}

void control::location(intptr_t control, const point& location) {
  if (control == 0) return;
  reinterpret_cast<control_handler*>(control)->control()->SetPosition({location.x(), location.y()});
}

drawing::size control::size(intptr_t control) {
  if (control == 0) return {};
  wxSize size = reinterpret_cast<control_handler*>(control)->control()->GetSize();
  return {size.GetWidth(), size.GetHeight()};
}

void control::size(intptr_t control, const drawing::size& size) {
  if (control == 0) return;
  reinterpret_cast<control_handler*>(control)->control()->SetSize(size.width(), size.height());
}

string control::text(intptr_t control) {
  if (control == 0) return {};
  //return reinterpret_cast<control_handler*>(control)->control()->GetLabel().ToStdString();
  intptr_t result = send_message(control, control, WM_GETTEXTLENGTH, 0, 0);
  string text(result, 0);
  result = send_message(control, control, WM_GETTEXT, result + 1, reinterpret_cast<intptr_t>(text.data()));
  return text;
}

void control::text(intptr_t control, const string& text) {
  if (control == 0) return;
  reinterpret_cast<control_handler*>(control)->control()->SetLabel(text);
  send_message(control, control, WM_SETTEXT, 0, reinterpret_cast<intptr_t>(reinterpret_cast<control_handler*>(control)->control()->GetLabel().ToStdString().c_str()));
}

bool control::visible(intptr_t control) {
  if (control == 0) return false;
  return reinterpret_cast<control_handler*>(control)->control()->IsShown();
}

void control::visible(intptr_t control, bool visible) {
  if (control == 0) return;
  if (visible)
   reinterpret_cast<control_handler*>(control)->control()->Show();
  else
    reinterpret_cast<control_handler*>(control)->control()->Hide();
}

void control::register_wnd_proc(intptr_t control, const delegate<intptr_t(intptr_t, int, intptr_t, intptr_t, intptr_t)>& wnd_proc) {
  if (control == 0) return;
  reinterpret_cast<control_handler*>(control)->wnd_proc += wnd_proc;
}

intptr_t control::send_message(intptr_t control, intptr_t hwnd, int msg, intptr_t wparam, intptr_t lparam) {
  if (hwnd == 0) return -1;
  return reinterpret_cast<control_handler*>(control)->send_message(hwnd, msg, wparam, lparam, 0);
}