#ifndef DATE_HPP
#define DATE_HPP

#include <cstdio>
#include <ctime>
#include <string>

std::string to_str(int value);

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

    typedef unsigned char monthDay;
    constexpr monthDay MonthDays[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

/**
 * @brief The Date class addresses the needs of the algorithm, 
 * such as easily incrementing days and creating variables with 
 * a specific date in a simple way. It also provides some additional functionality.
 * 
 */
class Date
{
    int year;
    Month::MonthName month;
    Month::monthDay day;

    uint8 hour;
    uint8 minute;
    uint8 seconds;

    void increment();
    static Month::MonthName monthNameFromString(const std::string &month_str);
public:
    Date();

    Date(int year, Month::MonthName month, Month::monthDay day);

    Date(int year, std::string month, Month::monthDay day);

    void print() const;

    /**
     * @brief Get the day (in year scale)
     * 
     * @return int 
     */
    int getYearDay() const;

    std::string getDate() const;

    std::string getTime() const;

    Date &operator++();

    Date operator++(int);
};

extern Date start_date;

#endif // DATE_HPP