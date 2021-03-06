#include "SettingsMenu.h"
#include "../../gamestates/MenuState.h"

#include <yaxl.h>
#include <iostream>
#include <fstream>

SettingsMenu::SettingsMenu() {
    for(unsigned int i = 0; i < 4; ++i) {
        MenuInputField *field = new MenuInputField(800.0f, 370.0f + (100 * i), 0.0f, 0.0f, Colors::WHITE);
        Box3 inputFieldSize(0.0f, 0.0f, 600.0f, 75.0f);
        field->setBoundingBox(inputFieldSize);
        _inputFields.push_back(field);
        addComponent(field);
    }

    for(unsigned int i = 0; i < 2; ++i) {
        MenuButton *button = new MenuButton(0.0f, 0.0f);
        _buttons.push_back(button);
        addComponent(button);
    }

    Box3 sizeBox(0.0f, 0.0f, 600.0f, 100.0f);

    _buttons[FULLSCREENBTN]->setText("Fullscreen: off");
    _buttons[FULLSCREENBTN]->setPosition(Vector3(300.0f, 820.0f));
    _buttons[FULLSCREENBTN]->setBoundingBox(sizeBox);
    _buttons[BACKBTN]->setText("Back");
    _buttons[BACKBTN]->setPosition(Vector3(1000.0f, 820.0f));
    _buttons[BACKBTN]->setBoundingBox(sizeBox);

    loadSettings();
    addActions();
    paint();
}

SettingsMenu::~SettingsMenu() {
}

void SettingsMenu::paint() {
    getGraphics().clear().beginPath().setFillStyle(phantom::Colors::WHITE).
        image("images/menu/bgsettings.png", 0.0f, 0.0f, getPhantomGame()->getViewPort().x, getPhantomGame()->getViewPort().y).
        stroke();

    for(MenuButton *button : _buttons)
        button->paint();

    for(MenuInputField *field : _inputFields)
        field->paint();
}

void SettingsMenu::update(const phantom::PhantomTime& time) {
    if(_repaint)
        paint();

    Composite::update(time);
}

void SettingsMenu::addActions() {
    std::function<void()> fullscreen, back;

    fullscreen = [this] () {
        string fullscreen = _buttons[FULLSCREENBTN]->text().substr(_buttons[FULLSCREENBTN]->text().find(' ') + 1, _buttons[FULLSCREENBTN]->text().size());
        stringstream stream;
        stream << "Fullscreen: " << (fullscreen == "on" ? "off" : "on");
        _buttons[FULLSCREENBTN]->setText(stream.str());
    };
    back = [this] () { saveToFile(); static_cast<MenuState*>(getParent())->navigate("/"); };

    _buttons[FULLSCREENBTN]->onClickFunction = fullscreen;
    _buttons[BACKBTN]->onClickFunction = back;
}

void SettingsMenu::loadSettings() {
    stringstream resolutionstream;
    resolutionstream << getPhantomGame()->getScreenSize().x << "x" << getPhantomGame()->getScreenSize().y;
    _inputFields[RESOLUTIONTXT]->text() = resolutionstream.str();
    stringstream soundstream;
    soundstream << getPhantomGame()->soundvol;
    _inputFields[SFXTXT]->text() = soundstream.str();
    stringstream musicstream;
    musicstream << getPhantomGame()->musicvol;
    _inputFields[MUSICTXT]->text() = musicstream.str();
    _buttons[FULLSCREENBTN]->text() = getPhantomGame()->fullscreen ? "Fullscreen: on" : "Fullscreen: off";

    Data data;
    try {
        data = Data::fromJson(yaxl::file::File("conf/settings.json").readAll());
    }
    catch (yaxl::file::FileException& e) {
        std::cout << e.what() << "No configuration found. Creating a new file." << endl;
    }

    _inputFields[USERNAMETXT]->text() = data("nickname").toString();
}

void SettingsMenu::saveToFile() {
    string username = _inputFields[USERNAMETXT]->text();
    string reswidth = _inputFields[RESOLUTIONTXT]->text().substr(0, _inputFields[RESOLUTIONTXT]->text().find('x'));
    string resheight = _inputFields[RESOLUTIONTXT]->text().substr(_inputFields[RESOLUTIONTXT]->text().find('x') + 1, _inputFields[RESOLUTIONTXT]->text().size());
    string soundvol = _inputFields[SFXTXT]->text().substr(0, _inputFields[SFXTXT]->text().find('x'));
    string musicvol = _inputFields[MUSICTXT]->text().substr(_inputFields[MUSICTXT]->text().find('x') + 1, _inputFields[MUSICTXT]->text().size());
    string fullscreen = _buttons[FULLSCREENBTN]->text().substr(_buttons[FULLSCREENBTN]->text().find(' ') + 1, _buttons[FULLSCREENBTN]->text().size());
    fullscreen = (fullscreen == "on" ? "1" : "0");

    ofstream phantomCfg("conf/phantomconfig.cfg");
    phantomCfg << "screenWidth " << reswidth << endl
        << "screenHeight " << resheight << endl
        << "fullscreen " << fullscreen << endl
        << "mousecursor 0" << endl
        << "soundvol " << soundvol << endl
        << "musicvol " << musicvol;
    phantomCfg.close();

    Data data;
    try {
        data = Data::fromJson(yaxl::file::File("conf/settings.json").readAll());
    }
    catch (yaxl::file::FileException& e) {
        std::cout << e.what() << "No configuration found. Creating a new file." << endl;
    }

    data("nickname") = username;

    ofstream settingsCfg("conf/settings.json");
    settingsCfg << data.toJson();
    settingsCfg.close();

    getPhantomGame()->parseConfigurationFile("conf/phantomconfig.cfg");
}