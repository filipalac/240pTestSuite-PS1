//Code stolen from  SGDK
//I replaced second argument of va_arg from u16/s16 to unsigned int/int to keep compiler happy

#include<psx.h>
#include<string.h>
#include<ctype.h>
#include<ctype.h>

#define u16 unsigned short
#define s16 short

static const char const uppercase_hexchars[] = "0123456789ABCDEF";
static const char const lowercase_hexchars[] = "0123456789abcdef";

static u16 skip_atoi(const char **s);

u16 skip_atoi(const char **s)
{
    u16 i = 0;

    while(isdigit(**s))
        i = (i * 10) + *((*s)++) - '0';

    return i;
}

u16 sg_vsprintf(char *buf, const char *fmt, va_list args)
{
    char tmp_buffer[12];
    s16 i;
    s16 len;
    s16 *ip;
    u16 num;
    char *s;
    const char *hexchars;
    char *str;
    s16 left_align;
    s16 plus_sign;
    s16 zero_pad;
    s16 space_sign;
    s16 field_width;
    s16 precision;

    for (str = buf; *fmt; ++fmt)
    {
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }

        space_sign = zero_pad = plus_sign = left_align = 0;

        // Process the flags
repeat:
        ++fmt;          // this also skips first '%'

        switch (*fmt)
        {
            case '-':
                left_align = 1;
                goto repeat;

            case '+':
                plus_sign = 1;
                goto repeat;

            case ' ':
                if ( !plus_sign )
                    space_sign = 1;

                goto repeat;

            case '0':
                zero_pad = 1;
                goto repeat;
        }

        // Process field width and precision

        field_width = precision = -1;

        if (isdigit(*fmt))
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            ++fmt;
            // it's the next argument
            field_width = va_arg(args, int);

            if (field_width < 0)
            {
                field_width = -field_width;
                left_align = 1;
            }
        }

        if (*fmt == '.')
        {
            ++fmt;

            if (isdigit(*fmt))
                precision = skip_atoi(&fmt);
            else if (*fmt == '*')
            {
                ++fmt;
                // it's the next argument
                precision = va_arg(args, int);
            }

            if (precision < 0)
                precision = 0;
        }

        if ((*fmt == 'h') || (*fmt == 'l') || (*fmt == 'L'))
            ++fmt;

        if (left_align)
            zero_pad = 0;

        switch (*fmt)
        {
            case 'c':
                if (!left_align)
                    while(--field_width > 0)
                        *str++ = ' ';

                *str++ = (unsigned char) va_arg(args, int);

                while(--field_width > 0)
                    *str++ = ' ';

                continue;

            case 's':
                s = va_arg(args, char *);

                if (!s)
                    s = "<NULL>";

                len = strnlen(s, precision);

                if (!left_align)
                    while(len < field_width--)
                        *str++ = ' ';

                for (i = 0; i < len; ++i)
                    *str++ = *s++;

                while(len < field_width--)
                    *str++ = ' ';

                continue;

            case 'p':
                if (field_width == -1)
                {
                    field_width = 2 * sizeof(void *);
                    zero_pad = 1;
                }

                hexchars = uppercase_hexchars;
                goto hexa_conv;

            case 'x':
                hexchars = lowercase_hexchars;
                goto hexa_conv;

            case 'X':
                hexchars = uppercase_hexchars;

hexa_conv:
                s = &tmp_buffer[12];
                *--s = 0;
                num = va_arg(args, unsigned int);

                if (!num)
                    *--s = '0';

                while(num)
                {
                    *--s = hexchars[num & 0xF];
                    num >>= 4;
                }

                num = plus_sign = 0;

                break;

            case 'n':
                ip = va_arg(args, s16*);
                *ip = (str - buf);
                continue;

            case 'u':
                s = &tmp_buffer[12];
                *--s = 0;
                num = va_arg(args, unsigned int);

                if (!num)
                    *--s = '0';

                while(num)
                {
                    *--s = (num % 10) + 0x30;
                    num /= 10;
                }

                num = plus_sign = 0;

                break;

            case 'd':
            case 'i':
                s = &tmp_buffer[12];
                *--s = 0;
                i = va_arg(args, int);

                if (!i)
                    *--s = '0';

                if (i < 0)
                {
                    num = 1;

                    while(i)
                    {
                        *--s = 0x30 - (i % 10);
                        i /= 10;
                    }
                }
                else
                {
                    num = 0;

                    while(i)
                    {
                        *--s = (i % 10) + 0x30;
                        i /= 10;
                    }
                }

                break;

            default:
                continue;
        }

        len = strnlen(s, precision);

        if (num)
        {
            *str++ = '-';
            field_width--;
        }
        else if (plus_sign)
        {
            *str++ = '+';
            field_width--;
        }
        else if (space_sign)
        {
            *str++ = ' ';
            field_width--;
        }

        if ( !left_align)
        {
            if (zero_pad)
            {
                while(len < field_width--)
                    *str++ = '0';
            }
            else
            {
                while(len < field_width--)
                    *str++ = ' ';
            }
        }

        for (i = 0; i < len; ++i)
            *str++ = *s++;

        while(len < field_width--)
            *str++ = ' ';
    }

    *str = '\0';

    return str - buf;
}

u16 sg_sprintf(char *buffer, const char *fmt, ...)
{
    va_list args;
    u16 i;

    va_start(args, fmt);
    i = sg_vsprintf(buffer, fmt, args);
    va_end(args);

    return i;
}
