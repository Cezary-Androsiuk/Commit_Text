#ifndef DATE_HPP
#define DATE_HPP

#include <cstdio>
#include <ctime>
#include <string>

std::string to_str(int value);

// that was a nice idea and I do not want to remove this
// namespace Month{
//     static constexpr uint8 January   = 31;
//     static constexpr uint8 February  = 29;
//     static constexpr uint8 March     = 31;
//     static constexpr uint8 April     = 30;
//     static constexpr uint8 May       = 31;
//     static constexpr uint8 June      = 30;
//     static constexpr uint8 July      = 31;
//     static constexpr uint8 August    = 31;
//     static constexpr uint8 September = 30;
//     static constexpr uint8 October   = 31;
//     static constexpr uint8 November  = 30;
//     static constexpr uint8 December  = 31;
//     static constexpr const uint8* Months[12] = {
//         &January,
//         &February,
//         &March,
//         &April,
//         &May,
//         &June,
//         &July,
//         &August,
//         &September,
//         &October,
//         &November,
//         &December
//     };
//     static constexpr const char* Months_names[12] = {
//         "January",
//         "February",
//         "March",
//         "April",
//         "May",
//         "June",
//         "July",
//         "August",
//         "September",
//         "October",
//         "November",
//         "December"
//     };
// };

typedef unsigned char monthDay;
typedef unsigned char uint8;

namespace Month
{
    enum MonthName
    {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };
    constexpr monthDay MonthDays[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

class Date
{
    int year;
    Month::MonthName month;
    monthDay day;

    uint8 hour;
    uint8 minute;
    uint8 seconds;

    void increment();

public:
    Date();

    Date(int year, Month::MonthName month, monthDay day);

    Date(int year, std::string month, monthDay day);

    void print() const;

    int getDays() const;

    std::string getDate() const;

    std::string getTime() const;

    Date &operator++();

    Date operator++(int);
};

extern Date start_date;

#endif // DATE_HPP