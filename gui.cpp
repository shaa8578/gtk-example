#include "gui.h"

#include <gtk/gtk.h>

#include "global.h"

//------------------------------------------------------------------------------
namespace priv_gui {

void setupConnections();
void setupMainWindow(GtkWindow* mainWindow);

GtkWidget* setupMenuBar();
GtkWidget* setupCentralWidget();
GtkWidget* setupFileChooserLayout();
GtkWidget* setupFindTextLayout();

} /* namespace priv_gui */

//------------------------------------------------------------------------------
void gui::setup(_GtkApplication* app) {
  gui::Global::mainWidget = gtk_application_window_new(app);
  auto main_window(GTK_WINDOW(Global::mainWidget));

  priv_gui::setupMainWindow(main_window);

  auto main_layout(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
  gtk_container_add(GTK_CONTAINER(main_window), main_layout);

  auto menu_bar(priv_gui::setupMenuBar());
  gtk_box_pack_start(GTK_BOX(main_layout), menu_bar, FALSE, FALSE, 2);

  auto central_widget(priv_gui::setupCentralWidget());
  gtk_box_pack_start(GTK_BOX(main_layout), central_widget, TRUE, TRUE, 0);

  priv_gui::setupConnections();

  gtk_widget_show_all(Global::mainWidget);
}

//------------------------------------------------------------------------------
void gui::showResultMessage(bool isSuccessSearch,
                            const std::string& findedWord) {
  std::string message;
  GtkMessageType msg_type(GTK_MESSAGE_OTHER);
  if (isSuccessSearch) {
    message.assign("Слово \"%s\" найдено!");
    msg_type = GTK_MESSAGE_INFO;
  } else {
    message.assign("\"%s\" в тексте нет.");
    msg_type = GTK_MESSAGE_WARNING;
  }
  auto dialog(gtk_message_dialog_new(
      GTK_WINDOW(gui::Global::mainWidget), GTK_DIALOG_MODAL, msg_type,
      GTK_BUTTONS_CLOSE, message.c_str(), findedWord.c_str()));
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

//------------------------------------------------------------------------------
void priv_gui::setupConnections() {
  g_signal_connect_swapped(gui::Global::menuItemExit, "activate",
                           G_CALLBACK(gui::Global::closeMainWindow), nullptr);
  g_signal_connect(GTK_BUTTON(gui::Global::chooseFileBtn), "clicked",
                   G_CALLBACK(gui::Global::choosingFile),
                   gui::Global::chooseFilePath);
  g_signal_connect(GTK_BUTTON(gui::Global::findBtn), "clicked",
                   G_CALLBACK(gui::Global::findWord), nullptr);
}

//------------------------------------------------------------------------------
void priv_gui::setupMainWindow(GtkWindow* mainWindow) {
  gtk_window_set_title(mainWindow, "Поиск слова в файле");
  gtk_window_set_default_size(mainWindow, 640, 480);
  gtk_window_set_position(mainWindow, GTK_WIN_POS_CENTER);
}

//------------------------------------------------------------------------------
GtkWidget* priv_gui::setupMenuBar() {
  gui::Global::menuItemExit = gtk_menu_item_new_with_label("Закрыть");

  auto menu(gtk_menu_new());
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), gui::Global::menuItemExit);

  auto menu_file(gtk_menu_item_new_with_label("Файл"));
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_file), menu);

  auto menu_bar(gtk_menu_bar_new());
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_file);
  return menu_bar;
}

//------------------------------------------------------------------------------
GtkWidget* priv_gui::setupCentralWidget() {
  auto central_wgt(gtk_frame_new(NULL));

  auto central_layout(gtk_box_new(GTK_ORIENTATION_VERTICAL, 8));
  auto central_box(GTK_BOX(central_layout));
  gtk_container_add(GTK_CONTAINER(central_wgt), central_layout);

  auto file_chooser_layout(setupFileChooserLayout());
  gtk_box_pack_start(central_box, file_chooser_layout, FALSE, FALSE, 0);

  auto find_text_layout(setupFindTextLayout());
  gtk_box_pack_start(central_box, find_text_layout, FALSE, FALSE, 0);

  return central_wgt;
}

//------------------------------------------------------------------------------
GtkWidget* priv_gui::setupFileChooserLayout() {
  auto file_chooser_layout(gtk_box_new(GTK_ORIENTATION_VERTICAL, 4));
  auto main_box(GTK_BOX(file_chooser_layout));

  auto file_label(gtk_label_new("Файл для поиска:"));
  gtk_label_set_justify(GTK_LABEL(file_label), GTK_JUSTIFY_LEFT);
  gtk_label_set_xalign(GTK_LABEL(file_label), 0.0f);
  gtk_box_pack_start(main_box, file_label, FALSE, FALSE, 0);

  auto file_layout(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  auto hbox(GTK_BOX(file_layout));
  gtk_box_pack_start(main_box, file_layout, FALSE, FALSE, 0);

  gui::Global::chooseFilePath = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(gui::Global::chooseFilePath), FALSE);
  gtk_entry_set_activates_default(GTK_ENTRY(gui::Global::chooseFilePath),
                                  FALSE);
  gtk_box_pack_start(hbox, gui::Global::chooseFilePath, TRUE, TRUE, 0);

  gui::Global::chooseFileBtn = gtk_button_new_with_label("Выбрать");
  gtk_box_pack_start(hbox, gui::Global::chooseFileBtn, FALSE, FALSE, 0);

  return file_chooser_layout;
}

//------------------------------------------------------------------------------
GtkWidget* priv_gui::setupFindTextLayout() {
  auto find_text_layout(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  auto main_box(GTK_BOX(find_text_layout));

  auto find_label(gtk_label_new("Искомый текст:"));
  gtk_label_set_justify(GTK_LABEL(find_label), GTK_JUSTIFY_LEFT);
  gtk_box_pack_start(main_box, find_label, FALSE, FALSE, 0);

  gui::Global::findText = gtk_entry_new();
  gtk_box_pack_start(main_box, gui::Global::findText, TRUE, TRUE, 0);

  gui::Global::findBtn = gtk_button_new_with_label("Найти");
  gtk_box_pack_start(main_box, gui::Global::findBtn, FALSE, FALSE, 0);

  return find_text_layout;
}
