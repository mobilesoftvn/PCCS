#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <iostream>
#include <deque>
#include "Test.h"
#include "../CompileConfig.h"

using namespace std;


class LIBEXPORT TestSuite {
    public:
        TestSuite();
        ~TestSuite();
        void run();
        void addTest(Test* test);
        void runSingle(Test* test);
    private:
        deque<Test*> _tests;
};


#endif	/* TESTSUITE_H */

