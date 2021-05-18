#include "global.h"

//------------------------------------------------------------------------------
GtkWidget* gui::Global::mainWidget = nullptr;
GtkWidget* gui::Global::menuItemExit = nullptr;
GtkWidget* gui::Global::chooseFilePath = nullptr;
GtkWidget* gui::Global::chooseFileBtn = nullptr;
GtkWidget* gui::Global::findText = nullptr;
GtkWidget* gui::Global::findBtn = nullptr;

//------------------------------------------------------------------------------
void gui::Global::closeMainWindow() {
  gtk_window_close(GTK_WINDOW(Global::mainWidget));
}

