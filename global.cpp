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

//------------------------------------------------------------------------------
void gui::Global::choosingFile(GtkButton*, gpointer fileEntry) {
  auto dialog(gtk_file_chooser_dialog_new(
      "Выбрать файл для поиска текста", GTK_WINDOW(mainWidget),
      GTK_FILE_CHOOSER_ACTION_OPEN, "_Отмена", GTK_RESPONSE_CANCEL, "_Выбрать",
      GTK_RESPONSE_ACCEPT, NULL));

  auto filter(gtk_file_filter_new());
  gtk_file_filter_add_pattern(filter, "*.txt");
  gtk_file_filter_set_name(filter, "Текстовый файл (*.txt)");

  auto file_chooser(GTK_FILE_CHOOSER(dialog));
  gtk_file_chooser_add_filter(file_chooser, filter);

  auto dlg_result = gtk_dialog_run(GTK_DIALOG(dialog));
  if (dlg_result == GTK_RESPONSE_ACCEPT) {
    auto file_name = gtk_file_chooser_get_filename(file_chooser);
    gtk_entry_set_text(GTK_ENTRY(fileEntry), file_name);
  }

  gtk_widget_destroy(dialog);
}
