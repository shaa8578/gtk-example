#pragma once
#include <gtk/gtk.h>

//------------------------------------------------------------------------------
namespace gui {

/** Списко глобальных переменных GUI */
struct Global {
  /** Главное окно */
  static GtkWidget* mainWidget;
  /** Меню Выход */
  static GtkWidget* menuItemExit;
  /** Поле ввода пути файла */
  static GtkWidget* chooseFilePath;
  /** Кнопка выбора пути файла */
  static GtkWidget* chooseFileBtn;
  /** Поле ввода текста поиска */
  static GtkWidget* findText;
  /** Кнопка начала поиска */
  static GtkWidget* findBtn;

  static void closeMainWindow();
  static void choosingFile(GtkButton* /*button*/, gpointer fileEntry);
};

} /* namespace gui */
