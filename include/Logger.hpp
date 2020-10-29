#pragma once
#include <iostream>
#include <tuple>
using namespace std;


class Logger {
public:
    static bool verbose;
    template<typename T>
    static void info(T t) {
        if(!Logger::verbose) {
            return;
        }
        cout << t ;
    }

    template<typename T, typename... Args>
    static void info(T t, Args... args)
    {
        if(!Logger::verbose) {
            return;
        }
        cout << t <<' ';
        Logger::info(args...);
    }

    template<typename T>
    static void error(T t) {
        if(!Logger::verbose) {
            return;
        }
        cout << t ;
    }

    template<typename T, typename... Args>
    static void error(T t, Args... args)
    {
        cout << t <<' ';
        Logger::info(args...);
    }

    
};