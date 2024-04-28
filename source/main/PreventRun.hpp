#ifndef PREVENT_RUN_HPP
#define PREVENT_RUN_HPP

#include <string>
#include <fstream>
#include <filesystem>

/**
 * @brief The PreventRun class prevents the script from running several times, 
 *  a situation which could lead to unexpected results. 
 */
class PreventRun
{
    const std::string running_file;

public:
    PreventRun(const std::string &logFile);
    ~PreventRun();
};

#endif // PREVENT_RUN_HPP