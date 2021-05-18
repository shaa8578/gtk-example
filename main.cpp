#include <gtk/gtk.h>

#include "gui.h"

//------------------------------------------------------------------------------
void activate(GtkApplication* app, gpointer /*user_data*/) {
  gui::setup(app);
}

//------------------------------------------------------------------------------
int main(int argc, char** argv) {
  GtkApplication* app(
      gtk_application_new("basecpp.hw06.part5", G_APPLICATION_FLAGS_NONE));

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  auto status(g_application_run(G_APPLICATION(app), argc, argv));
  g_object_unref(app);

  return status;
}
