#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <gtkmm.h>
#include "input_handler.hpp"

class UIWindow : public Gtk::Window{
    public:
        UIWindow();
        ~UIWindow() override;

    protected:
    //Box
    Gtk::Box m_main_box{Gtk::Orientation::VERTICAL, 10};

    //Widgets
    Gtk::Label m_label{"Minesweeper"};
    InputHandler m_input_handler{10};
};

class StartWindow : public UIWindow {
    public:
        StartWindow();
        ~StartWindow() override;

    protected:
    //Widgets
    Gtk::Scale m_bomb_scale;
    Gtk::Button m_start_button;

    //Signal handler
    void on_start_button_clicked();
};

class GameWindow : public UIWindow {
    public:
        GameWindow();
        ~GameWindow() override;

        //Shows the win/defeat overlay. Called once something detects the game has ended.
        void show_end_screen(bool won);

    protected:
    //Layout
    Gtk::Grid m_button_grid;
    Gtk::Overlay m_overlay;

    //Widgets
    Gtk::Button m_buttons[100];

    //End screen widgets
    Gtk::Box m_end_box{Gtk::Orientation::VERTICAL, 10};
    Gtk::Label m_end_label;
    Gtk::Button m_play_again_button{"Play Again"};
    Gtk::Button m_quit_button{"Quit"};

    //Signal handler
    void on_button_clicked(int id);
    void on_button_right_clicked(int id);
    void on_play_again_clicked();
    void on_quit_clicked();
};

#endif // UIMANAGER_H