#include "uimanager.hpp"
#include <gtkmm/application.h>


int main(int argc, char* argv[]){
  auto app = Gtk::Application::create("org.gtkmm.example");

  //Windows must be constructed and added after GApplication::startup,
  //which only fires once app->run() begins - so build them here, not in main().
  app->signal_activate().connect([app](){
    static StartWindow start_window;
    static GameWindow game_window;

    app->add_window(start_window);
    app->add_window(game_window);
    start_window.present();
  });

  return app->run(argc, argv);
}