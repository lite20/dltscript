#pragma once

#include <string>
#include <iostream>

namespace console
{
    void log(std::string type, std::string msg)
    {
        std::cout << "[" << type << "] " << msg << std::endl;
    }

    void crash(int code, std::string error)
    {
        log("FATAL", error);
        exit(code);
    }
}
