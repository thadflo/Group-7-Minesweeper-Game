#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <gtkmm.h>
#include "input_handler.hpp"

class UIWindow : public Gtk::Window{
    public:
        UIWindow();
        ~UIWindow() override;

    protected:
    //Layout
    Gtk::Box m_main_box{Gtk::Orientation::VERTICAL, 10};
    Gtk::Grid m_button_grid;

    //Widgets
    Gtk::Label m_label{"Fancy Minesweeper Wow"};
    Gtk::Button m_buttons[100];
    InputHandler m_input_handler{10};

    //Signal handler
    void on_button_clicked(int id);
};

#endif // UIMANAGER_H