#include <cstdlib>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "core/GameHub.h"

#include <sharedlib/serialization/Subset.h>

using namespace std;

int main(int argc, char** argv) {
    //GameHub server;

    double start = phantom::Util::getTime();

    Subset sub;
    sub("age")  = 3;
    sub("name") = "gerjo";
    sub("surname") = "meier";
    sub("length")  = 206;

    sub("bla1")("aa") = 123;
    sub("bla1")("ww")("www") = 234;
    sub("bla1")("bb") = 123;
    sub("bla1")("cc") = 123;
    sub("bla1")("ww")("ww")("ww")("ww") = 123;

    int age = sub("age");

    cout << "------" << endl;
    string str2 = sub.toJson();
    cout << str2 << endl;

    cout << "Size of one set: " << sizeof(sub) << endl;
    cout << endl << "delay: " << (phantom::Util::getTime() - start) << endl;

    return 0;
}
