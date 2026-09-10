#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class UIWindow : public Gtk::Window{
    public:
    UIWindow();
    ~UIWindow() override;

    protected:
    //Signal handlers:
    void on_button_clicked();

    //Member widgets:
    Gtk::Button m_button;
};

#endif // UIMANAGER_H