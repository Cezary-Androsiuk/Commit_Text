#ifndef PREVENT_RUN_HPP
#define PREVENT_RUN_HPP

#include <string>
#include <fstream>
#include <filesystem>

class PreventRun
{
    const std::string running_file;

public:
    PreventRun();
    ~PreventRun();
};

#endif // PREVENT_RUN_HPP