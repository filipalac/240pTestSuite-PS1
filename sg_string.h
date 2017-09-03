//Code stolen from SGDK
#pragma once

/**
 *  \file string.h
 *  \brief String manipulations
 *  \author Stephane Dallongeville
 *  \author Paspallas Dev
 *  \author Jack Nolddor
 *  \date 08/2011
 *
 * This unit provides basic null terminated string operations and type conversions.
 */

unsigned short sg_vsprintf(char *buf, const char *fmt, va_list args);
/**
 *  \brief
 *      Composes a string with the same text that would be printed if format was used on printf,
 *      but instead of being printed, the content is stored as a C string in the buffer pointed by str.
 *
 *  \param buffer
 *      Destination string (it must be large enough to receive result).
 *  \param fmt
 *      C string that contains the text to be written to destination string.<br />
 *      It can optionally contain embedded format specifiers.
 *
 *  \param ... (additional arguments)
 *      Depending on the format string, the function may expect a sequence of additional arguments, <br>
 *      each containing a value to be used to replace a format specifier in the format string.
 *
 *      There should be at least as many of these arguments as the number of values specified in the format specifiers. <br>
 *      Additional arguments are ignored by the function.
 *
 *  \return On success, the total number of characters written is returned..
 *
 *  Copy the string pointed by 'fmt' param to the 'buffer' param.<br>
 *  If 'fmt' includes format specifiers (subsequences beginning with %), the additional arguments following format are
 *  formatted and inserted in the resulting string replacing their respective specifiers
 *
 */
unsigned short sg_sprintf(char *buffer,const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
