#pragma once

namespace Core
{
	namespace Debug
	{
		#define ASSERT(condition, message) if(!condition) throw std::runtime_error(message);
		#define DEBUG_LOG(VAR,...)(Log::DebugLog(__FILE__,__LINE__,VAR,__VA_ARGS__));
	}
}
