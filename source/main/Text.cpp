#include "Text.hpp"

Text::Text() : text_filled(false), missing_text_file(false)
{
    this->getState();
}
Text::~Text()
{ /*this->setState();*/
}

void Text::getState()
{
    std::fstream file(Text::file_path, std::ios::in);
    if (!file.good())
    {
        printf("cannot open file %s to get state\n", Text::file_path);
        this->missing_text_file = true;
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

void Text::setState()
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

void Text::print()
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

int Text::test(Date date = Date())
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

const bool &Text::isTextFileMissing() const
{
    return this->missing_text_file;
}