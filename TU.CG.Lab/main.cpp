#include <iostream>

#include "Applications/Application.hpp"

int main(const int argc, const char** argv)
{
	try
	{
		Applications::Application app;

		app.Run();

		return 0;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return -1;
	}
}
