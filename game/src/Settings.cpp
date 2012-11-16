#include "Settings.h"
#include <sstream>
#include <sharedlib/serialization/Data.h>
#include <yaxl.h>
#include <file/FileException.h>
#include <phantom.h>

string Settings::SERVER_HOST = "localhost"; // "145.92.7.231"; //
int Settings::SERVER_PORT    = 8075;
string Settings::NICKNAME    = "default";

void Settings::load(void) {

    // A little hack so we can easily run multiple client from the same computer
    // without having to change the username all the time.
    stringstream ss;
    ss << "default-" << std::fixed << phantom::Util::getTime();
    Settings::NICKNAME = ss.str();

    try {
        Data data = Data::fromJson(yaxl::file::File("conf/settings.json").readAll());


        if(data("serverhost").toString() != "") SERVER_HOST = data("serverhost").toString();
        if(data("serverport").toString() != "") SERVER_PORT = data("serverport");

        NICKNAME    = data("nickname").toString();
    } catch (yaxl::file::FileException& e) {
        std::cout << e.what() << "Proceeding with default settings." << endl;
    }
}
