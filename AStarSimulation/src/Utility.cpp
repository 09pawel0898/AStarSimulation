#include "pch.h"
#include "./Utility.h"

namespace Utility
{
	void set_origin_to_center(sf::Text &text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
	}

	void set_origin_to_center(sf::Sprite &sprite)
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
	}

	void normalise_vec(vec2f& vec)
	{
		float len = sqrt(vec.x * vec.x + vec.y * vec.y);
		vec = vec2f(vec.x / len, vec.y / len);
	}

	void cls(void)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD());

	}

	void console_cursor(bool flag)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
		cursorInfo.bVisible = flag;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

	void hide_console(void)
	{
		ShowWindow(GetConsoleWindow(), 0);
	}

	double deg_to_rad(double degree)
	{
		return (degree * (3.14159265359 / 180));
	}

	double rad_to_deg(double rad)
	{
		return (rad * 180)/3.14159265359 ;

	}
}