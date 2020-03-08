#pragma once

#include <algorithm>

#include "Public/SString.h"

#include "Public/SResourceConf.h"


namespace SEngine{

String GResourcePath = RESOURCE_ROOT;

String GetFontPath(String name)
{
	String ret = GResourcePath + "/Fonts/" + name;
	//std::replace(ret.begin(), ret.end(), '/', '\\');
	return ret;
}
}


