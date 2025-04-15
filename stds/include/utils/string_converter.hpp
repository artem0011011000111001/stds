#pragma once

#ifndef _STDS_STRING_CONVERTER_
#define _STDS_STRING_CONVERTER_

#include "config/types.hpp"

STDS_START

HIDDEN_STDS_START
EXPR_STDS_START

#if SUPPORT_CHAR8
inline char32_t decode_utf8(const char_8_t*& p) {
    const unsigned char* s = reinterpret_cast<const unsigned char*>(p);
    char32_t result = 0;
    if (s[0] < 0x80) {
        result = s[0];
        ++p;
    }
    else if ((s[0] & 0xE0) == 0xC0) {
        result = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
        p += 2;
    }
    else if ((s[0] & 0xF0) == 0xE0) {
        result = ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
        p += 3;
    }
    else if ((s[0] & 0xF8) == 0xF0) {
        result = ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
        p += 4;
    }
    else {
        ++p;
    }
    return result;
}
#endif // SUPPORT_CHAR8

inline char32_t decode_utf16(const char16_t*& p) {
    char16_t lead = *p++;
    if (lead >= 0xD800 && lead <= 0xDBFF) {
        char16_t trail = *p;
        if (trail >= 0xDC00 && trail <= 0xDFFF) {
            ++p;
            return (((lead - 0xD800) << 10) | (trail - 0xDC00)) + 0x10000;
        }
        else {
            // Invalid surrogate pair
            return 0xFFFD; // replacement char
        }
    }
    if (lead >= 0xDC00 && lead <= 0xDFFF) {
        // Isolated trailing surrogate
        return 0xFFFD;
    }
    return lead;
}

inline char32_t decode_utf32(const char32_t*& p) {
    return *p++;
}

inline int encode_utf8(char32_t cp, char* out) {
    if (cp < 0x80) {
        out[0] = static_cast<char>(cp);
        return 1;
    }
    else if (cp < 0x800) {
        out[0] = static_cast<char>((cp >> 6) | 0xC0);
        out[1] = static_cast<char>((cp & 0x3F) | 0x80);
        return 2;
    }
    else if (cp < 0x10000) {
        out[0] = static_cast<char>((cp >> 12) | 0xE0);
        out[1] = static_cast<char>(((cp >> 6) & 0x3F) | 0x80);
        out[2] = static_cast<char>((cp & 0x3F) | 0x80);
        return 3;
    }
    else {
        out[0] = static_cast<char>((cp >> 18) | 0xF0);
        out[1] = static_cast<char>(((cp >> 12) & 0x3F) | 0x80);
        out[2] = static_cast<char>(((cp >> 6) & 0x3F) | 0x80);
        out[3] = static_cast<char>((cp & 0x3F) | 0x80);
        return 4;
    }
}

#if SUPPORT_CHAR8
inline HSTDS_::sz_t strlen_utf8(const char_8_t* s) {
    HSTDS_::sz_t len = 0;
    while (*s) {
        decode_utf8(s);
        ++len;
    }
    return len;
}
#endif // SUPPORT_CHAR8

inline HSTDS_::sz_t strlen_utf16(const char16_t* s) {
    HSTDS_::sz_t len = 0;
    while (*s) {
        decode_utf16(s);
        ++len;
    }
    return len;
}

inline HSTDS_::sz_t strlen_utf32(const char32_t* s) {
    HSTDS_::sz_t len = 0;
    while (*s++) ++len;
    return len;
}

EXPR_STDS_END
HIDDEN_STDS_END

STDS_END

#endif // _STDS_STRING_CONVERTER_