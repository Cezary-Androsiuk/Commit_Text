#ifndef FUNC_HPP
#define FUNC_HPP

#include <string>
#include <thread>
#include <chrono>
#include <filesystem>

#include "Date.hpp"
#include "Text.hpp"

std::string makeMyDayAction(Date date);

void makeTaskScheduler();

#endif // FUNC_HPP