#ifndef FUNC_HPP
#define FUNC_HPP

#include <string>
#include <thread>
#include <chrono>
#include <filesystem>

#include "Date.hpp"
#include "Formula.hpp"
#include "../json_XD.hpp"

/**
 * @brief saves the status of the last run to a file
 * 
 * @param logFile path to the log file
 * @param statusToLog the status you wish to write to the file, preferred numbers 0-9
 * @param date current date
 */
void logStatus(const std::string &logFile, const std::string &statusToLog, const Date &date);

/**
 * @brief manages the operations that can occur during formula refreshment 
 * 
 * @param date current date
 * @param formulaFile file with formula
 * @return std::string returns status that will be saved as a log (prefered number in range 0-9)
 */
std::string makeMyDayAction(const Date &date, const std::string &formulaFile);

#endif // FUNC_HPP