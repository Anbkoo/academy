#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include "Interface.h"

namespace fs = std::filesystem;
using dll_function = IPlugin*(*)();

class Lib_Download
	{
	public:
	Lib_Download(const fs::directory_entry& p)
		{
		hGetProcIDDLL = LoadLibrary(p.path().c_str());
		if (!hGetProcIDDLL)
			{
			std::cout << "couldn`t open library " << p.path() << std::endl;
			}
		}

	auto Load_Function(const std::string name_function)
		{
		return reinterpret_cast<dll_function>(GetProcAddress(hGetProcIDDLL, name_function.c_str()));
		}

	bool check_function(dll_function func)
		{
		if (!func)
			{
			std::cout << "couldn`t open function" << std::endl;
			return false;
			}
		return true;
		}

	~Lib_Download()
		{
		FreeLibrary(hGetProcIDDLL);
		}
	private:
		HMODULE hGetProcIDDLL;
	};