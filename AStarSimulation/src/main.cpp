#include "pch.h"
#include "./Application.h"
#include "./Utility.h"

int main(void)
{
	Utility::console_cursor(false);
	Application app;
	app.run();
}