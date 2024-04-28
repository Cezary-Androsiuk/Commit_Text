#include "Date.hpp"

std::string to_str(int value)
{
    if (value < 0)
        return "";
    else if (value < 10)
        return std::string("0") + std::to_string(value);
    else
        return std::to_string(value);
}

void Date::increment()
{
    if (this->day >= Month::MonthDays[this->month - 1])
    {
        if (this->month >= Month::December)
        {
            this->month = Month::January;
            this->day = 1;
            this->year++;
        }
        else
        {
            this->month = static_cast<Month::MonthName>(this->month + 1);
            this->day = 0;
        }
    }
    else
    {
        this->day++;
    }
}

Month::MonthName Date::monthNameFromString(const std::string &month_str)
{
    if(false); // following code will look nicer and even UwU
    else if (month_str == "January")    return Month::January;
    else if (month_str == "February")   return Month::February;
    else if (month_str == "March")      return Month::March;
    else if (month_str == "April")      return Month::April;
    else if (month_str == "May")        return Month::May;
    else if (month_str == "June")       return Month::June;
    else if (month_str == "July")       return Month::July;
    else if (month_str == "August")     return Month::August;
    else if (month_str == "September")  return Month::September;
    else if (month_str == "October")    return Month::October;
    else if (month_str == "November")   return Month::November;
    else if (month_str == "December")   return Month::December;
    else
    {
        printf("Unknown '%s' month\n", month_str.c_str());
        return Month::January;
    }
}

Date::Date()
{
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);

    this->day = now->tm_mday;
    this->month = static_cast<Month::MonthName>(now->tm_mon + 1);
    this->year = now->tm_year + 1900;
    this->hour = now->tm_hour;
    this->minute = now->tm_min;
    this->seconds = now->tm_sec;
}

Date::Date(int year, Month::MonthName month, Month::monthDay day)
{
    this->year = year;
    this->month = month;
    this->day = day;

    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);
    this->hour = now->tm_hour;
    this->minute = now->tm_min;
    this->seconds = now->tm_sec;
}

Date::Date(int year, std::string month, Month::monthDay day)
    : Date(year, Date::monthNameFromString(month), day)
{}

void Date::print() const
{
    printf("Date: %d %d %d\n", this->day, this->month, this->year);
}

int Date::getYearDay() const
{
    int days = 0;
    for (int i = 0; i < 12; i++)
    {
        if (this->month != static_cast<Month::MonthName>(i + 1))
            days += Month::MonthDays[i];
        else
        {
            days += this->day;
            return days;
        }
    }
    return 0;
}

std::string Date::getDate() const
{
    return to_str(this->year) + "-" + to_str(this->month) + "-" + to_str(this->day);
}

std::string Date::getTime() const
{
    return to_str(this->hour) + "-" + to_str(this->minute) + "-" + to_str(this->seconds);
}

Date &Date::operator++()
{
    this->increment();
    return *this;
}

Date Date::operator++(int)
{
    Date tmp(*this);
    this->increment();
    return tmp;
}
