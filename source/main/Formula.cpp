#include "Formula.hpp"

Formula::Formula(const std::string &formulaFile) : m_formulaFile(formulaFile), text_filled(false), missing_text_file(false)
{
}
Formula::~Formula()
{
}

void Formula::load()
{
    std::fstream file(m_formulaFile, std::ios::in);
    if (!file.good())
    {
        printf("cannot open formula file %s to get state\n", m_formulaFile.c_str());
        this->missing_text_file = true;
        return;
    }

    std::string buffer;
    int currentRowIndex{0};
    while (std::getline(file, buffer))
    {
        if (buffer.empty())
            break;

        if (currentRowIndex >= Formula::formulaRows)
        {
            printf("error: given formula file has MORE rows than expected! expected: %d rows\n", Formula::formulaRows);
            file.close();
            return;
        }

        if (buffer.size() != Formula::formulaColumns)
        {
            printf("error: in formula file, row(%d) has %s columns than expected! expected: %d columns\n", 
                currentRowIndex, (buffer.size() > Formula::formulaColumns ? "MORE" : "LESS"), Formula::formulaColumns);
            file.close();
            return;
        }

        // cci stands for currentColumnIndex
        for (int cci = 0; cci < buffer.size(); cci++)
        {
            this->text[cci][currentRowIndex] = buffer[cci];
        }
        currentRowIndex++;
    }
    file.close();

    if (currentRowIndex != Formula::formulaRows)
    {
        printf("error: given formula file has LESS rows than expected! expected: %d rows\n", Formula::formulaRows);
        return;
    }

    // set info that formula was readed from file
    this->text_filled = true;
}

void Formula::save()
{
    if (!this->text_filled)
    {
        printf("formula was not readed from '%s' file!\n", m_formulaFile.c_str());
        return;
    }

    std::fstream file(m_formulaFile, std::ios::out);
    if (!file.good())
    {
        printf("cannot open formula file %s to save state\n", m_formulaFile.c_str());
        return;
    }

    for (int y = 0; y < Formula::formulaRows; y++)
    {
        for (int x = 0; x < Formula::formulaColumns; x++)
            file << this->text[x][y];

        if (y < Formula::formulaRows - 1)
            file << "\n";
    }
    file.close();
}

void Formula::print() const
{
    if (!this->text_filled)
    {
        printf("formula was not readed from '%s' file!\n", m_formulaFile.c_str());
        return;
    }

    for (int y = 0; y < Formula::formulaRows; y++)
    {
        for (int x = 0; x < Formula::formulaColumns; x++)
            printf("%c", this->text[x][y]);
        printf("\n");
    }
}

int Formula::update(const Date &start_date, const Date &date)
{
    // check if algorithm was not started for example 2024-01-20 (or ealier), but start date was set on 2024-02-10
    int days_since_start = date.getYearDay() - start_date.getYearDay();
    if (days_since_start < 0)
        return BEFORE_START;

    // current day position in formula text
    uint8 column = (days_since_start / Formula::formulaRows) * 2;
    uint8 row = days_since_start % Formula::formulaRows;
    uint8 digit = 0;

    // check if algorithm goes through all foreseen fields in text[formulaColumns][formulaRows] array
    if(column >= formulaColumns || row >= formulaRows)
        return AFTER_END;

    // each day contains two fields but script checks only the first one for easy interpretation
    char current_char = this->text[column][row];

    // check if char matches to the field that shouldn't be filled
    if (current_char == Formula::empty_not_setted) 
    {
        // assume that the other field is also empty to not change anything in "empty" day
        return NONE_FIELD_AND_SETTED;
    }
    // check if char matches to the field that should be filled but was not started yet
    else if (current_char == Formula::fill_not_setted) 
    {
        // change "xx" to digit "00"
        digit = 0;
    }
    else // digits
    {
        uint8 digit = this->getDigitFromText(column, row);
        // check if field in formula was filled
        if (digit >= 99)
            return VALUE_FIELD_AND_FILLED_MAX;

        // increase previous digit
        digit++;
    }
    
    // set digit to text array
    this->setDigitToText(column, row, digit);
    return digit;
}

void Formula::setDigitToText(uint8 column, uint8 row, uint8 digit)
{
    this->text[column][row] = digit/10+ '0'; // first digit 
    this->text[column+1][row] = digit%10 + '0'; // second digit
}

uint8 Formula::getDigitFromText(uint8 column, uint8 row)
{
    uint8 dg1 = this->text[column][row] - '0'; // first digit 
    uint8 dg2 = this->text[column+1][row] - '0'; // second digit
    return dg1 * 10 + dg2;
}

const bool &Formula::isTextFileMissing() const
{
    return this->missing_text_file;
}