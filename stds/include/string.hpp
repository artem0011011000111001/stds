#pragma once

#ifndef _STDS_STRING_
#define _STDS_STRING_

#include "ptr.hpp"
#include "utils/string_converter.hpp"

STDS_START

HIDDEN_STDS_START

#ifdef _WIN32
using ch = wchar_t;
using other_ch = char;
#else
using ch = char;
using other_ch = wchar_t;
#endif

HIDDEN_STDS_END

HIDDEN_STDS_START
EXPER_STDS_START

template<class _Allocator = HSTDS_::base_alloc<HSTDS_::ch>>
class string : public HSTDS_::base_null_t {

    using ch = HSTDS_::ch;
    using other_ch = HSTDS_::other_ch;
    using size_type = HSTDS_::sz_t;
    using allocator = _Allocator;
    using data = ch*;
    using pointer = ptr<ch, allocator>;

    pointer base;

    ch encode_to_ch(char32_t cp) {
#ifdef _WIN32
        // ch = wchar_t -> UTF-16
        if constexpr (sizeof(ch) == 2) {
            if (cp < 0x10000) return static_cast<ch>(cp);
            // We trim if surrogates are not supported
            return L'?';
        }
        else {
            return static_cast<ch>(cp);
        }
#else
        // ch = char -> UTF-8
        if constexpr (sizeof(ch) == 1) {
            // Cut to the first byte
            char tmp[4];
            int n = HSTDS_::encode_utf8(cp, tmp);
            return static_cast<ch>(tmp[0]); // Only first byte
        }
        else {
            return static_cast<ch>(cp);
        }
#endif
    }

#if SUPPORT_CHAR8
    pointer convert(const char_8_t* s) {
        if (!s) return null;

        const char_8_t* p = s;
        size_type len = HSTDS_::strlen_utf8(s);

        pointer result = make_ptr<ch, nullptr, allocator>(len);
        for (size_type i = 0; i < len; ++i) {
            char32_t code = HSTDS_::decode_utf8(p);
            result[i] = encode_to_ch(code);
        }

        return result;
    }
#endif // SUPPORT_CHAR8

    pointer convert(const char16_t* s) {
        if (!s) return null;

        const char16_t* p = s;
        size_type len = HSTDS_::strlen_utf16(s);
        
        pointer result = make_ptr<ch, nullptr, allocator>(len);
        for (size_type i = 0; i < len; ++i) {
            char32_t code = HSTDS_::decode_utf16(p);
            result[i] = encode_to_ch(code);
        }

        return result;
    }

    pointer convert(const char32_t* s) {
        if (!s) return null;

        const char32_t* p = s;
        size_type len = HSTDS_::strlen_utf32(s);

        pointer result = make_ptr<ch, nullptr, allocator>(len);
        for (size_type i = 0; i < len; ++i) {
            result[i] = encode_to_ch(*p++);
        }

        return result;
    }

    pointer convert(const ch* s) {
        if (!s) return null;

        const ch* p = s;
        size_type len = string::strlen(s);

        pointer result = make_ptr<ch, nullptr, allocator>(len);
        for (size_type i = 0; i < len; ++i) {
            result[i] = p[i];
        }

        return result;
    }

    pointer convert(const other_ch* s) {
        if (!s) return null;

        const other_ch* p = s;
        size_type len = string::strlen(s);

        pointer result = make_ptr<ch, nullptr, allocator>(len);
        for (size_type i = 0; i < len; ++i) {
            result[i] = encode_to_ch(static_cast<char32_t>(p[i]));
        }

        return result;
    }

    void reset() {
        base_null_t::reset();
        base = null;
    }

    size_type strlen(const wchar_t* str) {
        size_type len = 0;
        while (str && str[len]) ++len;
        return len;
    }

    size_type strlen(const char* str) {
        size_type len = 0;
        while (str && str[len]) ++len;
        return len;
    }

    void init_from(pointer str) {
        if (!str.is_valid()) throw code::zero_allocation;
        base = HSTDS_::move(str);
        _is_null_ = false;
    }

public:
    string() { reset(); }

    string(data str) { init_from(convert(str)); }
    string(other_ch* str) { init_from(convert(str)); }
#if SUPPORT_CHAR8
    string(HSTDS_::char_8_t* str) { init_from(convert(str)); }
#endif // SUPPORT_CHAR8
    string(char16_t* str) { init_from(convert(str)); }
    string(char32_t* str) { init_from(convert(str)); }

    data get() {
        check_is_null_and_throw(code::reference_to_null);
        return base.get();
    }
};

EXPER_STDS_END
HIDDEN_STDS_END

STDS_END

#endif // _STDS_STRING_