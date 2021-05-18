#pragma once
#include <string>

//------------------------------------------------------------------------------
struct _GtkApplication;

//------------------------------------------------------------------------------
namespace gui {

void setup(_GtkApplication* app);
void showResultMessage(bool isSuccessSearch, const std::string& findedWord);

} /* namespace gui */
