#pragma once

#include <exception>
#include <string>
#include <windows.h>

namespace Common
{
	class SException : public std::exception
	{
	public:
		SException(const char* const Message, HRESULT HR = S_OK);
		HRESULT HR() const;
		virtual const char* what() const;
	private:
		HRESULT HRField;
	};

	inline void ThrowIfFailed(HRESULT HR, const char* const Message = "")
	{
		if (FAILED(HR))
		{
			throw SException(Message, HR);
		}
	}
}