#ifndef TEXT_HPP
#define TEXT_HPP

#include <cstdio>
#include <string>
#include <fstream>

#include "Date.hpp"

typedef unsigned char uint8;


class Formula
{
public:
    // 48 x 7 is the size of the text area
    static constexpr uint8 formulaColumns{48 * 2};
    static constexpr uint8 formulaRows{7};

    // signs used in formula
    static constexpr char empty_not_setted = ' ';
    static constexpr char fill_not_setted = 'x';

    enum UpdateState
    {
        BEFORE_START = -1, // when algorithm have start date x and it is date x-1

        NONE_FIELD_AND_SETTED = -2, // when field shouldn't be updated that day (char is empty_not_setted)

        // when changed from fill_not_setted to 00, then return 0
        // when changed from 00 to 01, then return 1
        // when changed from 01 to 01, then return 2
        // ...
        // when changed from 98 to 99, then return 99
        VALUE_FIELD_AND_FILLED_MAX = -5, // when 99

        AFTER_END = -6 // when algorithm goes through all fields in formula
    };

private:
    char text[Formula::formulaColumns][Formula::formulaRows];
    const std::string m_formulaFile;
    bool text_filled;
    bool missing_text_file;

public:
    Formula(const std::string &formulaFile);
    ~Formula();

    /**
     * @brief reads formula from file and save it to local variable 
     */
    void load();
    /**
     * @brief saves formula from local variable to file 
     */
    void save();

    /**
     * @brief prints formula from variable to screen
     */
    void print() const;

    /**
     * @brief updates local formula depends date and formula
     * 
     * @param start_date day on which the algorithm starts
     * @param date current date
     * @return int - update result
     */
    int update(const Date &start_date, const Date &date = Date());

private:
    /**
     * @brief Set the Digit To Text object // deam, that desc. was genereated by vscode
     * 
     * @param column column of the local formula field
     * @param row row of the local formula field
     * @param digit number which will be stored in the variable
     */
    void setDigitToText(uint8 column, uint8 row, uint8 digit);
    /**
     * @brief Get the Digit From Text object // deam, vscode did it again
     * 
     * @param column column of the local formula field
     * @param row row of the local formula field
     * @return uint8 number which was readed from the variable
     */
    uint8 getDigitFromText(uint8 column, uint8 row);

public:
    const bool &isTextFileMissing() const;
};

#endif // TEXT_HPP