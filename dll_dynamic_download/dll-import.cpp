#include <string>
#include <iostream>
#include "LibraryDownload.h"

int main(int argc, char* argv[])
	{
	if (argc < 2) 
		{
		std::cout << "write a path to folder" << std::endl;
		exit(1);
		}
		
	constexpr auto func_name = "create_plugin";
	for (auto& p : fs::directory_iterator(argv[1]))
		{
		Lib_Download a(p);
		auto func = a.Load_Function(func_name);
		if (!a.check_function(func))
			{
			continue;
			}
		auto* plugin = func();
		std::cout << plugin->GetName() << std::endl;

		delete plugin;
		plugin = nullptr;
		}

	return EXIT_SUCCESS;
	}