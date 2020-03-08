#pragma once

#include <string>

#include "STypes.h"

namespace SEngine {

// Types for strings.
using WString = std::basic_string<wchar_t, std::char_traits<wchar_t>>;
using UTF16String = std::basic_string<char16_t, std::char_traits<char16_t>>;
using UTF32String = std::basic_string<char32_t, std::char_traits<char32_t>>;
using String = std::basic_string<char, std::char_traits<char>>;

static constexpr uchar UTF8_MASKBITS = uchar(0x3F);
static constexpr uchar UTF8_MASKBYTE = uchar(0x80);
static constexpr uchar UTF8_MASK2BYTES = uchar(0xC0);
static constexpr uchar UTF8_MASK3BYTES = uchar(0xE0);
static constexpr uchar UTF8_MASK4BYTES = uchar(0xF0);
static constexpr uchar UTF8_MASK5BYTES = uchar(0xF8);
static constexpr uchar UTF8_MASK6BYTES = uchar(0xFC);

//static size_t decode_utf8(const String& src, WString& dst) noexcept;
static size_t decode_utf8(CStr src, size_t len, WString& ret) noexcept;

WString string2wstring(const String& src) noexcept
{
	WString ret;
	decode_utf8(src.c_str(), src.size(), ret);
	return ret;
}

static size_t decode_utf8(CStr src, size_t len, WString& dst) noexcept
{
	size_t i = 0;
	for (; i < len;)
	{
		wchar_t ch;

		if ((src[i] & UTF8_MASK4BYTES) == UTF8_MASK4BYTES)
		{
			if constexpr (sizeof(wchar_t) == 2)
			{
				// UTF16
				wchar_t first = wchar_t(src[i] & 0x03);
				wchar_t second = wchar_t(src[i + 1] & UTF8_MASKBITS);
				wchar_t third = wchar_t(src[i + 2] & UTF8_MASKBITS);
				wchar_t forth = wchar_t(src[i + 3] & UTF8_MASKBITS);
				ch = 0xD800U | (first << 8) | (second << 2) | (third >> 4);
				dst.push_back(ch);
				ch = 0xDE00U | ((third & 0x0F) << 6) | forth;
			}
			else
			{
				// UTF32
				uint32 first = uint32(src[i] & 0x07U) << 18;
				uint32 second = uint32(src[i + 1] & UTF8_MASKBITS) << 12;
				uint32 third = uint32(src[i + 2] & UTF8_MASKBITS) << 6;
				uint32 forth = uint32(src[i + 3] & UTF8_MASKBITS);
				ch = wchar_t(first | second | third | forth);

			}
			i += 4;
		}

		// 1110xxxx 10xxxxxx 10xxxxxx
		else if ((src[i] & UTF8_MASK3BYTES) == UTF8_MASK3BYTES)
		{
			wchar_t first = wchar_t(wchar_t(src[i] & 0x0FU) << 12);
			wchar_t second = wchar_t(wchar_t(src[i + 1] & UTF8_MASKBITS) << 6);
			wchar_t third = wchar_t(src[i + 2] & UTF8_MASKBITS);
			ch = wchar_t(first | second | third);
			i += 3;
		}
		// 110xxxxx 10xxxxxx
		else if ((src[i] & UTF8_MASK2BYTES) == UTF8_MASK2BYTES)
		{
			wchar_t first = wchar_t(wchar_t(src[i] & 0x1FU) << 6);
			wchar_t second = wchar_t(src[i + 1] & UTF8_MASKBITS);
			ch = wchar_t(first | second);
			i += 2;
		}
		// 0xxxxxxx
		else if (uchar(src[i]) < UTF8_MASKBYTE)
		{
			ch = wchar_t(src[i]);
			i += 1;
		}
		else
		{
			assert(0);
		}

		dst.push_back(ch);
	}
	return i;
}

}
