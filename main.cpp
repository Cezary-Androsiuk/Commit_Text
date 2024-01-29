#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <filesystem>

// g++ main.cpp -o main.exe && .\main.exe

typedef unsigned char monthDay;
typedef unsigned char uint8;

// nice and I do not want to remove this
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

std::string to_str(int value)
{
    if( value < 0) return "";
    else if( value < 10)
        return std::string("0") + std::to_string(value);
    else
        return std::to_string(value);
}

class Date
{
    int year;
    Month::MonthName month;
    monthDay day;

    uint8 hour;
    uint8 minute;
    uint8 seconds;

    void increment()
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

public:
    Date()
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

    Date(int year, Month::MonthName month, monthDay day)
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

    Date(int year, std::string month, monthDay day)
    {
        this->year = year;
        if (month == "January")         this->month = Month::January;
        else if (month == "February")   this->month = Month::February;
        else if (month == "March")      this->month = Month::March;
        else if (month == "April")      this->month = Month::April;
        else if (month == "May")        this->month = Month::May;
        else if (month == "June")       this->month = Month::June;
        else if (month == "July")       this->month = Month::July;
        else if (month == "August")     this->month = Month::August;
        else if (month == "September")  this->month = Month::September;
        else if (month == "October")    this->month = Month::October;
        else if (month == "November")   this->month = Month::November;
        else if (month == "December")   this->month = Month::December;
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

    void print() const
    {
        printf("Date: %d %d %d\n", this->day, this->month, this->year);
    }

    int getDays() const
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

    std::string getDate() const
    {
        return to_str(this->year) + "-" + to_str(this->month) + "-" + to_str(this->day);
    }
    
    std::string getTime() const
    {
        return to_str(this->hour) + "-" + to_str(this->minute) + "-" + to_str(this->seconds);
    }

    Date &operator++()
    {
        this->increment();
        return *this;
    }

    Date operator++(int)
    {
        Date tmp(*this);
        this->increment();
        return tmp;
    }
};

Date start_date(2024, Month::January, 28);

class Text
{
public:
    // 48 x 7 is the size of the text area
    static constexpr char x{48 * 2};
    static constexpr char y{7};
    static constexpr const char *file_path = "text";
    static constexpr char empty_not_setted = ' ';
    static constexpr char empty_setted = '-';
    static constexpr char fill_not_setted = 'x';
    static constexpr char fill_not_setted_0 = '0';
    enum TestState
    {
        BEFORE_START = -1, // when start is x but today is x-1

        NONE_FIELD_AND_SETTED = -2, // when ' '
        // NONE_FIELD_AND_ALREADY_SETTED = -3,   // when '-'

        // when setted from xx to 00 ten returns 0
        // when setted from 00 to 01 ten returns 1
        // when setted from 01 to 01 ten returns 2
        // ...
        // when setted from 98 to 99 ten returns 99
        VALUE_FIELD_AND_FILLED_MAX = -5, // when 99
    };

private:
    char text[Text::x][Text::y];
    bool text_filled = false;
    // int test_state;

public:
    Text() { this->getState(); }
    ~Text() { /*this->setState();*/ }

    void getState()
    {
        std::fstream file(Text::file_path, std::ios::in);
        if (!file.good())
        {
            printf("cannot open file %s to get state\n", Text::file_path);
            return;
        }

        std::string buffer;
        int y{0};
        while (std::getline(file, buffer))
        {
            if (buffer.empty())
                break;

            if (y >= Text::y)
            {
                printf("error: given file has MORE rows than expected!\n");
                file.close();
                return;
            }

            if (buffer.size() != Text::x)
            {
                printf("error: %lld row has %s columns than expected!\n", buffer.size() > Text::x ? "MORE" : "LESS");
                file.close();
                return;
            }

            for (int x = 0; x < buffer.size(); x++)
            {
                this->text[x][y] = buffer[x];
            }
            y++;
        }
        file.close();

        if (y != Text::y)
        {
            printf("error: given file has LESS rows than expected!\n");
            return;
        }
        this->text_filled = true;
    }

    void setState()
    {
        if (!this->text_filled)
        {
            printf("state is not defined by setState()\n");
            return;
        }
        std::fstream file(Text::file_path, std::ios::out);
        if (!file.good())
        {
            printf("cannot open file %s to save state\n", this->file_path);
            return;
        }

        for (int y = 0; y < Text::y; y++)
        {
            for (int x = 0; x < Text::x; x++)
                file << this->text[x][y];

            if (y < Text::y - 1)
                file << "\n";
        }
        file.close();
    }

    void print()
    {
        if (!this->text_filled)
        {
            printf("state is not defined by setState()\n");
            return;
        }

        for (int y = 0; y < Text::y; y++)
        {
            for (int x = 0; x < Text::x; x++)
                printf("%c", this->text[x][y]);
            printf("\n");
        }
    }

    int test(Date date = Date())
    {
        int days_since_start = date.getDays() - start_date.getDays();
        if (days_since_start < 0)
            return BEFORE_START;

        uint8 current_x = (days_since_start / Text::y) * 2;
        uint8 current_y = days_since_start % Text::y;

        char current_char = this->text[current_x][current_y];

        if (current_char == Text::empty_not_setted) // '  '
        {
            // this->text[current_x][current_y] = Text::empty_setted;
            // this->text[current_x + 1][current_y] = Text::empty_setted;
            return NONE_FIELD_AND_SETTED;
        }
        // else if(current_char == Text::empty_setted) // '--'
        // {
        //     return NONE_FIELD_AND_ALREADY_SETTED;
        // }
        else if (current_char == Text::fill_not_setted) // 'xx'
        {
            this->text[current_x][current_y] = Text::fill_not_setted_0;
            this->text[current_x + 1][current_y] = Text::fill_not_setted_0;
            return 0; // as a digit
        }
        else // digits
        {
            uint8 dg1 = this->text[current_x][current_y] - '0';
            uint8 dg2 = this->text[current_x + 1][current_y] - '0';
            uint8 digit = dg1 * 10 + dg2;
            if (digit >= 99)
                return VALUE_FIELD_AND_FILLED_MAX;

            digit++;
            // printf("digit: %d\n", digit);
            this->text[current_x][current_y] = digit / 10 + '0';
            this->text[current_x + 1][current_y] = digit % 10 + '0';
            return digit;
        }
    }
};

std::string makeMyDayAction(Date date)
{
    Text text;
    text.print();
    printf("\n\n");

    for (int i = 0; i < 100; i++)
    {
        int state = text.test(date);
        if (state == Text::BEFORE_START)
        {
            printf("before start\n");
            return "9"; //"Before start date";
        }
        else if (state == Text::NONE_FIELD_AND_SETTED)
        {
            printf("empty\n");
            return "1"; //"Today's field should remain empty";
        }
        else if (state == Text::VALUE_FIELD_AND_FILLED_MAX)
        {
            printf("max\n");
            return "2"; //"Today's field has already been filled";
        }

        text.print();
        printf("\n\n");

        text.setState();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::system("git add text");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::string commit("git commit -m \"");
        commit += date.getDate() + " " + date.getTime() + " Index: " + to_str(i) + "\"";
        std::system(commit.c_str());
    }
    // text.print();
    std::system("git push");
    return " "; //"Today's field has been filled correctly";
}


class PreventRun
{
    const std::string running_file = "program_is_running";
public:
    PreventRun(){
        if(std::filesystem::exists(this->running_file)){
            std::ofstream file("scheduler.log", std::ios::app);
            file << "(prevented run) ";
            file.close();
            exit(0);
        }
        std::ofstream file(this->running_file);
        file << "hi :)\n";
        file.close();

    }
    ~PreventRun(){
        if(std::filesystem::exists(this->running_file))
            std::filesystem::remove(this->running_file);
    }
};




int main()
{
    PreventRun prevent_run;
    Date date;
    std::ofstream file;

    file.open("scheduler.log", std::ios::app);
    file << "start(" << date.getDate() << " " << date.getTime() << ") - ";
    file.close();

    std::string result = makeMyDayAction(date);

    file.open("scheduler.log", std::ios::app);
    file << "(" << result << ") - ";
    file << "end(" << date.getDate() << " " << date.getTime() << ")\n";
    file.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

/*

"Well, this code is a mess, and I don't want to make it clearer... 
I will just leave it as it is."

*/