#include "pch.h"
#include "./Application.h"
#include "./Utility.h"

int main(void)
{
	srand(time(NULL));
	Utility::console_cursor(false);
	//Utility::hide_console();
	Application app;
	app.run();
}