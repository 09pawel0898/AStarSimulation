#include "pch.h"
#include "PathFinder.h"

PathFinder::PathFinder(Graph graph, const vec2i& start)
	: mGraph(graph)
{
	static int IDgen = 0;
	mId = IDgen++;
	Node node;
	node.x = 3;
	node.y = 3;
	//default value
	mStart = &graph.get_nodes()[start.x * graph.WIDTH + start.y];
	mEnd = &graph.get_nodes()[(graph.HEIGHT -2) * graph.WIDTH + graph.WIDTH - 2];
}



void PathFinder::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mIsVisible)
	{
		draw_start_and_end(target);
		draw_visited_nodes(target);
		draw_found_path(target);
	}
}

void PathFinder::draw_start_and_end(sf::RenderTarget& target) const
{
	sf::RectangleShape rec;
	rec.setFillColor(sf::Color::Red);
	rec.setSize(vec2f(32, 32));
	rec.setPosition(mStart->x * 64 + 16, mStart->y * 64 + 16);
	target.draw(rec);
	rec.setFillColor(sf::Color::Blue);
	rec.setPosition(mEnd->x * 64 + 16, mEnd->y * 64 + 16);
	target.draw(rec);
}

void PathFinder::draw_visited_nodes(sf::RenderTarget& target) const
{
	sf::RectangleShape rec;
	rec.setFillColor(sf::Color(0,255,0,50));
	rec.setSize(vec2f(32, 32));

	Node* nodes = mGraph.get_nodes();

	for (int x = 0; x < mGraph.WIDTH; x++)
	{
		for (int y = 0; y < mGraph.HEIGHT; y++)
		{
			if (nodes[y * mGraph.WIDTH + x].visited == true && &nodes[y * mGraph.WIDTH + x] != mEnd && &nodes[y * mGraph.WIDTH + x] != mStart)
			{
				rec.setPosition((float)(x * 64 + 16), (float)(y * 64 + 16));
				target.draw(rec);
			}
		}
	}
}

void PathFinder::draw_found_path(sf::RenderTarget& target) const
{
	if (mEnd != nullptr)
	{
		Node* pivot = mEnd;
		while (pivot->parent != nullptr)
		{
			sf::Vertex line[] = 
			{ 
				sf::Vertex(vec2f((float)(pivot->x * 64 + 64 / 2),(float)(pivot->y * 64 + 64 / 2))),
				sf::Vertex(vec2f((float)(pivot->parent->x * 64 + 64 / 2),(float)(pivot->parent->y * 64 + 64 / 2))) 
			};
			sf::Color color = sf::Color::Green;
			line[0].color = line[1].color = color;
			target.draw(line, 2, sf::Lines);
			pivot = pivot->parent;
		}
	}
} 

void PathFinder::solve_AStar(void)
{
	Node* nodes = mGraph.get_nodes();

	for (int x = 0; x < mGraph.WIDTH; x++)
	{
		for (int y = 0; y < mGraph.HEIGHT; y++)
		{
			nodes[y * mGraph.WIDTH + x].visited = false;
			nodes[y * mGraph.WIDTH + x].globalGoal = INFINITY;
			nodes[y * mGraph.WIDTH + x].localGoal = INFINITY;
			nodes[y * mGraph.WIDTH + x].parent = nullptr;
		}
	}

	auto distance = [](Node* a, Node* b)
	{
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	};

	auto heuristic = [distance](Node* a, Node* b)
	{
		return distance(a, b);
	};

	Node* nodeCurrent = mStart;
	mStart->localGoal = 0.0f;
	mStart->globalGoal = heuristic(mStart,mEnd);

	std::list<Node*> notTestedNodes;
	notTestedNodes.push_back(mStart);

	bool finish(false);

	do
	{
		notTestedNodes.sort
		([](const Node* lhs, const Node* rhs) 
		{ 
			return lhs->globalGoal < rhs->globalGoal; 
		});

		while (!notTestedNodes.empty() && notTestedNodes.front()->visited)
			notTestedNodes.pop_front();

		if (notTestedNodes.empty())
			break;

		nodeCurrent = notTestedNodes.front();
		nodeCurrent->visited = true;

		for (auto neighbour : nodeCurrent->neighbours)
		{
			if (!neighbour->visited && !neighbour->obstacle)
				notTestedNodes.push_back(neighbour);

			float fPossiblyLowerGoal = nodeCurrent->localGoal + distance(nodeCurrent, neighbour);

			if (fPossiblyLowerGoal < neighbour->localGoal)
			{
				neighbour->parent = nodeCurrent;
				neighbour->localGoal = fPossiblyLowerGoal;
				neighbour->globalGoal = neighbour->localGoal + heuristic(neighbour, mEnd);
			}
		}

		if (mShortest)
		{
			if (notTestedNodes.empty())
				finish = true;
		}
		else if (!mShortest)
		{
			if (!(!notTestedNodes.empty() && nodeCurrent != mEnd))
				finish = true;
		}
	} while (!finish);
}

void PathFinder::change_path_type(void)
{
	mShortest = (mShortest) ? false : true;
}

Node* PathFinder::get_start(void) const
{
	return mStart;
}

Node* PathFinder::get_end(void) const
{
	return mEnd;
}

void PathFinder::set_start(Node* node)
{
	mStart = node;
}

void PathFinder::set_end(Node* node)
{
	mEnd = node;
}

void PathFinder::show_path(void)
{
	mIsVisible = true;
}

void PathFinder::hide_path(void)
{
	mIsVisible = false;
}

bool PathFinder::get_visibility(void) const
{
	return mIsVisible;
}