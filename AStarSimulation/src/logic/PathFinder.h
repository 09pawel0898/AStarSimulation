#pragma once

struct Node;
#include "Graph.h"

enum class Direction
{
	L,R,U,D,LU,RU,LD,RD, NUL
};

class PathFinder : public sf::Drawable
{
private:
	uint8_t mId;
	Node* mStart;
	Node* mEnd;
	Graph mGraph;
	bool mShortest = true;
	bool mIsVisible = false;
	bool& mPathExist;

	void draw_start_and_end(sf::RenderTarget& target) const;
	void draw_visited_nodes(sf::RenderTarget& target) const;
	void draw_found_path(sf::RenderTarget& target) const;

	
public:

	PathFinder(Graph graph, const vec2i& start, bool& pathExist);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void solve_AStar(void);
	void change_path_type(void);

	Node* get_start(void) const;
	Node* get_end(void) const;
	Direction get_direction(void) const;
	void set_start(Node* node);
	void set_end(Node* node);
	
	void show_path(void);
	void hide_path(void);
	bool get_visibility(void) const;

};