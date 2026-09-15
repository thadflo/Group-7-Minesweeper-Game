#include "uimanager.hpp"

using namespace std;

constexpr int GRID_SIZE = 10;
constexpr int TILE_COUNT = GRID_SIZE * GRID_SIZE;
constexpr int TILE_SIZE_PX = 42;
constexpr int GRID_SPACING = 3;

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
  
  m_button_grid.set_row_spacing(GRID_SPACING);
  m_button_grid.set_column_spacing(GRID_SPACING);
  m_button_grid.set_halign(Gtk::Align::CENTER);   // center the grid
  m_button_grid.set_valign(Gtk::Align::CENTER);

  // Attach buttons to grid
  for (int i = 0; i < TILE_COUNT; ++i){
    m_buttons[i].set_label(to_string(i + 1));
    m_buttons[i].set_size_request(TILE_SIZE_PX, TILE_SIZE_PX); 
    // Connect click signal using a lambda to pass the button ID
    m_buttons[i].signal_clicked().connect(
      sigc::bind(sigc::mem_fun(*this, &UIWindow::on_button_clicked), i + 1)
    );

    auto right_click = Gtk::GestureClick::create();
    right_click->set_button(GDK_BUTTON_SECONDARY);
    right_click->signal_pressed().connect([this, id = i + 1](int, double, double) {
      on_button_right_clicked(id);
    });
    m_buttons[i].add_controller(right_click);

    int col = i % GRID_SIZE;
    int row = i / GRID_SIZE;
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

void UIWindow::on_button_right_clicked(int id){
  m_input_handler.handle_tile_click(id, ClickType::RIGHT);
}
