#include "uimanager.hpp"

using namespace std;

constexpr int GRID_SIZE = 10;
constexpr int TILE_COUNT = GRID_SIZE * GRID_SIZE;
constexpr int TILE_SIZE_PX = 42;
constexpr int GRID_SPACING = 3;

UIWindow::UIWindow(){
  /* UIWindow manages the GTK UI */
  set_title("Minesweeper");
  set_resizable(false);
  //create css provider for GTK
  auto css_provider = Gtk::CssProvider::create();
  //set CSS theming for buttons
  css_provider->load_from_data(
        "window grid button.normal { background: #695f65; color: #695f65; }"
        "window grid button.normal:hover, window grid button.normal:active { background: #695f65; color: #695f65; }"
        "window grid button.clicked { background: #a0a09b; color: #a0a09b; }"
        "window grid button.clicked:hover, window grid button.clicked:active, window grid button.clicked:disabled { background: #a0a09b; color: #a0a09b; opacity: 1; }"
    ); 
    //override user theming for GTK, ensuring our CSS takes priority
    auto default_display = Gdk::Display::get_default();
    if (default_display) {
        Gtk::StyleProvider::add_provider_for_display( 
            default_display, 
            css_provider, 
            GTK_STYLE_PROVIDER_PRIORITY_USER 
        ); 
    }
  
  m_main_box.set_margin(10);
  m_main_box.set_spacing(8);
  set_child(m_main_box);
  //add game title to top-center
  m_label.set_halign(Gtk::Align::CENTER);
  m_main_box.append(m_label);
  //add button grid to bottom
  m_button_grid.set_row_spacing(GRID_SPACING);
  m_button_grid.set_column_spacing(GRID_SPACING);
  m_button_grid.set_halign(Gtk::Align::CENTER);   // center the grid
  m_button_grid.set_valign(Gtk::Align::CENTER);

  //attach buttons to grid
  for (int i = 0; i < TILE_COUNT; ++i){
    //set up css and size
    m_buttons[i].add_css_class("normal");
    m_buttons[i].set_size_request(TILE_SIZE_PX, TILE_SIZE_PX);
    m_buttons[i].set_label("");
    //add signals for left click
    m_buttons[i].signal_clicked().connect(
      sigc::bind(sigc::mem_fun(*this, &UIWindow::on_button_clicked), i + 1)
    );
    //add signals for right click
    auto right_click = Gtk::GestureClick::create();
    right_click->set_button(GDK_BUTTON_SECONDARY);
    right_click->signal_pressed().connect([this, id = i + 1](int, double, double) {
      on_button_right_clicked(id);
    });
    m_buttons[i].add_controller(right_click);
    //attach button to grid at correct point
    int col = i % GRID_SIZE;
    int row = i / GRID_SIZE;
    m_button_grid.attach(m_buttons[i], col, row, 1, 1);
  }

  //add the grid to the bottom of the main box
  m_main_box.append(m_button_grid);
}

UIWindow::~UIWindow(){}

void UIWindow::on_button_clicked(int id){
  /* Handler for left button clicks */
  //sends signal to the game input handler
  m_input_handler.handle_tile_click(id, ClickType::LEFT);
  int idx = id - 1;
  //Do not let player leftclick on a flagged tile
  if (m_buttons[idx].get_label() == "🚩") return;
  m_buttons[idx].remove_css_class("normal");
  m_buttons[idx].add_css_class("clicked");
  m_buttons[idx].set_sensitive(false);

  //then down here update the labels for this tile and surrounding tiles
  //perhaps m_input_handler should return an array of affected tiles or smt
}

void UIWindow::on_button_right_clicked(int id){
  /*Handler for right clicks on button*/
  m_input_handler.handle_tile_click(id, ClickType::RIGHT);
  int idx = id - 1;
  //If flag already exists, remove it
  if (m_buttons[idx].get_label() == "🚩") {
    m_buttons[idx].set_label("");
    return;
  }
  //add flag picture
  /*
  auto* img = Gtk::make_managed<Gtk::Image>();
  gtk_image_set_from_file(GTK_IMAGE(img->gobj()), "flag.svg");
  img->set_pixel_size(TILE_SIZE_PX - 12);
  m_buttons[idx].set_child(*img);
  */
  //rigt now just using this emoji, the svg was too large or smth and cause issues
  m_buttons[idx].set_label("🚩");
}
