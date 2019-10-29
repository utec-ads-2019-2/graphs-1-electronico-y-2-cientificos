//
// Created by alejandro on 2019-10-29.
//

#ifndef GRAPHS_1_ELECTRONICO_Y_2_CIENTIFICOS_TESTER_H
#define GRAPHS_1_ELECTRONICO_Y_2_CIENTIFICOS_TESTER_H


#include <stdexcept>
#include <iostream>
#include <assert.h>
#include <string.h>


using namespace std;

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

class Tester {
public:
    static void execute();
};



#endif //GRAPHS_1_ELECTRONICO_Y_2_CIENTIFICOS_TESTER_H
