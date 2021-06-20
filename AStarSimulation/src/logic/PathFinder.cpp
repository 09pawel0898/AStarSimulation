#include "pch.h"
#include "PathFinder.h"
#include "Graph.h"

PathFinder::PathFinder(Graph* graph)
	:	mGraph(graph)
{
	Node node;
	node.x = 3;
	node.y = 3;
	//default value
	mStart = &graph->get_nodes()[1 * graph->WIDTH + 1];
	mEnd = &graph->get_nodes()[(graph->HEIGHT -1) * graph->WIDTH + graph->WIDTH - 2];
}



void PathFinder::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	draw_start_and_end(target);
	draw_visited_nodes(target);
	draw_found_path(target);
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
	rec.setFillColor(sf::Color::Green);
	rec.setSize(vec2f(32, 32));

	for (int x = 0; x < mGraph->WIDTH; x++)
	{
		for (int y = 0; y < mGraph->HEIGHT; y++)
		{
			if (mGraph->get_nodes()[y * mGraph->WIDTH + x].visited == true)
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
			line[0].color = sf::Color::Cyan;
			line[1].color = sf::Color::Cyan;
			target.draw(line, 2, sf::Lines);
			pivot = pivot->parent;
		}
	}
} 

void PathFinder::solve_AStar(void)
{
	Node* nodes = mGraph->get_nodes();

	for (int x = 0; x < mGraph->WIDTH; x++)
	{
		for (int y = 0; y < mGraph->HEIGHT; y++)
		{
			nodes[y * mGraph->WIDTH + x].visited = false;
			nodes[y * mGraph->WIDTH + x].globalGoal = INFINITY;
			nodes[y * mGraph->WIDTH + x].localGoal = INFINITY;
			nodes[y * mGraph->WIDTH + x].parent = nullptr;
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

