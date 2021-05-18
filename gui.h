#pragma once
#include <gtk/gtk.h>

#include <string>

//------------------------------------------------------------------------------
namespace gui {

void setup(GtkApplication* app);

} /* namespace gui */

//------------------------------------------------------------------------------
namespace priv_gui {

void setupConnections();
void setupMainWindow(GtkWindow* mainWindow);

GtkWidget* setupMenuBar();
GtkWidget* setupCentralWidget();
GtkWidget* setupFileChooserLayout();
GtkWidget* setupFindTextLayout();

void showResultMessage(bool isSuccessSearch, const std::string& findedWord);

} /* namespace priv_gui */
