#pragma once

namespace Utility
{

	class VisibleVector : public sf::Drawable, sf::Vector2f
	{
	private:
		sf::VertexArray line;
		sf::Vector2f start;
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(line);
		}
	public:
		VisibleVector()
			: sf::Vector2f(), line(sf::Lines, 2), start(0, 0)
		{}
		VisibleVector(float startX = 0, float startY = 0, float x = 1, float y = 1)
			: sf::Vector2f(x, y), line(sf::Lines, 2), start(startX, startY)
		{
			line[0].position = sf::Vector2f(startX, startY);
			line[1].position = sf::Vector2f(x, y);
			line[0].color = sf::Color::Red;
			line[1].color = sf::Color::Red;
		}
		void update(float startX, float startY, float x, float y)
		{
			this->x = x;
			this->y = y;
			start.x = startX;
			start.y = startY;
			line[0].position = sf::Vector2f(startX, startY);
			line[1].position = sf::Vector2f(x, y);
		}	
	};

	template <typename T>
	std::string to_string(const T &value);

	template <typename T>
	sf::Vector2i to_vector2i(sf::Vector2<T> vector);

	template <typename T>
	float get_lenght(sf::Vector2<T> vector);

	double deg_to_rad(double degree);
	double rad_to_deg(double rad);

	void set_origin_to_center(sf::Text &text);
	void set_origin_to_center(sf::Sprite &sprite);
	
	void cls(void);
	void console_cursor(bool flag);
	void hide_console(void);
}

#include "./Utility.inl"