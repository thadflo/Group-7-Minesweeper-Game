#include "uimanager.hpp"
#include <iostream>
using namespace std;

UIWindow::UIWindow(){
  set_title("Minesweeper");
  set_default_size(300, 200);
  
  m_main_box.set_margin(5);
  set_child(m_main_box);
  m_label.set_margin_bottom(10);
  m_main_box.append(m_label);
  
  m_button_grid.set_row_spacing(5);
  m_button_grid.set_column_spacing(5);
  m_button_grid.set_expand(true); // Let the grid fill remaining space

  // Attach buttons to grid
  for (int i = 0; i < 100; ++i){
    m_buttons[i].set_label("Button " + to_string(i + 1));
    
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

//tbh not sure what this thing is
UIWindow::~UIWindow(){}

void UIWindow::on_button_clicked(int id){
  m_input_handler.handle_tile_click(id, ClickType::LEFT);
}
