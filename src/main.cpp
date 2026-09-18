#include "uimanager.hpp"
#include <gtkmm/application.h>

int main(int argc, char* argv[]){
  auto app = Gtk::Application::create("org.gtkmm.example");
  Gtk::Window::set_remove_on_hide(false);

  // Windows must be constructed and added after GApplication::startup,
  // which only fires once app->run() begins - so build them here, not in main().
  app->signal_activate().connect([app]() {
    static StartWindow start_window;
    static GameWindow game_window;

    auto* start_window_ptr = &start_window;
    auto* game_window_ptr = &game_window;

    start_window.signal_close_request().connect([app]() -> bool {
      app->quit();
      return true;
    }, false);

    game_window.signal_close_request().connect([app]() -> bool {
      app->quit();
      return true;
    }, false);

    start_window_ptr->m_input_handler.on_start_game = [start_window_ptr, game_window_ptr](int num_bombs) {
      game_window_ptr->start_game(num_bombs);
      game_window_ptr->present();
      start_window_ptr->hide();
    };

    game_window_ptr->m_input_handler.on_retry = [start_window_ptr, game_window_ptr]() {
      game_window_ptr->reset_game();
      game_window_ptr->hide();
      start_window_ptr->present();
    };

    game_window_ptr->m_input_handler.on_close = [app]() {
      app->quit();
    };

    app->add_window(start_window);
    app->add_window(game_window);
    start_window.present();
  });

  return app->run(argc, argv);
}