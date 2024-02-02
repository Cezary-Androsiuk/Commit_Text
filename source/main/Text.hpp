#ifndef TEXT_HPP
#define TEXT_HPP

#include <cstdio>
#include <string>
#include <fstream>

#include "Date.hpp"

typedef unsigned char uint8;

// Date start_date(2024, Month::January, 28);

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
    bool text_filled;
    bool missing_text_file;

public:
    Text();
    ~Text();

    void getState();

    void setState();

    void print();

    int test(Date date);

    const bool &isTextFileMissing() const;
};

#endif // TEXT_HPP