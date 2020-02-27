#include "Public/SException.h"
#include <sstream>

namespace Common
{
	SException::SException(const char* const Message, HRESULT HR /* = S_OK */): 
		std::exception(Message), HRField(HR)
	{

	}

	HRESULT SException::HR() const
	{
		return HRField;
	}

	const char* SException::what() const
	{
		std::stringstream WhatSS;
		WhatSS << exception::what() << "(HR: " << HRField << ")";
		return WhatSS.str().c_str();
	}
}