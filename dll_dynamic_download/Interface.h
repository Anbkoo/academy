#pragma once
#include <string>

class IPlugin
	{
	public:
		IPlugin() = default;
		virtual const char* GetName() const = 0;
		virtual ~IPlugin() = default;
	};