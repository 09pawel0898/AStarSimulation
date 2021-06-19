template <typename T>
std::string Utility::to_string(const T &value)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}

template <typename T>
sf::Vector2i Utility::to_vector2i(sf::Vector2<T> vector)
{
	return sf::Vector2i(int(vector.x), int(vector.y));
}

template <typename T>
float Utility::get_lenght(sf::Vector2<T> vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}