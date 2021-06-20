#pragma once

struct Node;
class Graph;

class PathFinder : public sf::Drawable
{
private:
	Node* mStart = nullptr;
	Node* mEnd = nullptr;
	Graph* mGraph;

	void draw_start_and_end(sf::RenderTarget& target) const;
	void draw_visited_nodes(sf::RenderTarget& target) const;
	void draw_found_path(sf::RenderTarget& target) const;

	void solve_AStar(void);
public:

	PathFinder(Graph* graph);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Node* get_start(void) const;
	Node* get_end(void) const;
};