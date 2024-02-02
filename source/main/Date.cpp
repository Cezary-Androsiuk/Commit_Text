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

Date::Date(int year, Month::MonthName month, monthDay day)
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

Date::Date(int year, std::string month, monthDay day)
{
    this->year = year;
    if (month == "January")
        this->month = Month::January;
    else if (month == "February")
        this->month = Month::February;
    else if (month == "March")
        this->month = Month::March;
    else if (month == "April")
        this->month = Month::April;
    else if (month == "May")
        this->month = Month::May;
    else if (month == "June")
        this->month = Month::June;
    else if (month == "July")
        this->month = Month::July;
    else if (month == "August")
        this->month = Month::August;
    else if (month == "September")
        this->month = Month::September;
    else if (month == "October")
        this->month = Month::October;
    else if (month == "November")
        this->month = Month::November;
    else if (month == "December")
        this->month = Month::December;
    else
    {
        printf("Unknown '%s' month\n", month);
        this->month = Month::January;
    }
    this->day = day;

    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);
    this->hour = now->tm_hour;
    this->minute = now->tm_min;
    this->seconds = now->tm_sec;
}

void Date::print() const
{
    printf("Date: %d %d %d\n", this->day, this->month, this->year);
}

int Date::getDays() const
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

Date start_date(2024, Month::January, 28);