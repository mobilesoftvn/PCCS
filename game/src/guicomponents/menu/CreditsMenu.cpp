#include "CreditsMenu.h"
#include "../../gamestates/MenuState.h"
#include <functional>

CreditsMenu::CreditsMenu() {
    MenuButton *button = new MenuButton(556.5f, 760.0f);
    _buttons.push_back(button);
    addComponent(button);

    _buttons[BACKBTN]->setText("back");
    
    paint();
    addActions();
}

CreditsMenu::~CreditsMenu() {
}

void CreditsMenu::paint() {
    getGraphics().clear().beginPath().setFillStyle(Colors::WHITE).image("images/menu/bgcredits.png", 0.0f, 0.0f, getPhantomGame()->getViewPort().x, getPhantomGame()->getViewPort().y).fill();

    for(MenuButton *button : _buttons)
        button->paint();
}

void CreditsMenu::update(const phantom::PhantomTime& time) {
    Composite::update(time);
}

void CreditsMenu::addActions() {
    std::function<void()> back = [this] {
        static_cast<MenuState*>(getParent())->navigate("/");
    };

    _buttons[BACKBTN]->onClickFunction = back;
}