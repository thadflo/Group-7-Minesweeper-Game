#include "uimanager.hpp"
#include <iostream>
using namespace std;

UIWindow::UIWindow(){
  set_title("Minesweeper");
  set_resizable(false);

  auto css_provider = Gtk::CssProvider::create();
  css_provider->load_from_data(
      "button.clicked { background: #3a3a3a; color: #aaa; }"
  );
  Gtk::StyleContext::add_provider_for_display(
      Gdk::Display::get_default(),
      css_provider,
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
);
  
  m_main_box.set_margin(10);
  m_main_box.set_spacing(8);
  set_child(m_main_box);

  m_label.set_halign(Gtk::Align::CENTER);
  m_main_box.append(m_label);
  
  m_button_grid.set_row_spacing(3);
  m_button_grid.set_column_spacing(3);
  m_button_grid.set_halign(Gtk::Align::CENTER);   // center the grid
  m_button_grid.set_valign(Gtk::Align::CENTER);

  // Attach buttons to grid
  for (int i = 0; i < 100; ++i){
    m_buttons[i].set_label("Button " + to_string(i + 1));
    m_buttons[i].set_size_request(42, 42); 
    // Connect click signal using a lambda to pass the button ID
    m_buttons[i].signal_clicked().connect(
      sigc::bind(sigc::mem_fun(*this, &UIWindow::on_button_clicked), i + 1)
    );

    int col = i % 10;
    int row = i / 10;
    m_button_grid.attach(m_buttons[i], col, row, 1, 1);
  }

  // Add the grid to the bottom of the main box
  m_main_box.append(m_button_grid);
}

UIWindow::~UIWindow(){}

void UIWindow::on_button_clicked(int id){
  m_input_handler.handle_tile_click(id, ClickType::LEFT);

  int idx = id - 1;
  m_buttons[idx].add_css_class("clicked");
  m_buttons[idx].set_sensitive(false);

  //then down here update the label
}
