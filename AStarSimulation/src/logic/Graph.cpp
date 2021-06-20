#include "pch.h"
#include "Graph.h"
#include "../res/ResourceManager.h"


bool Graph::init_nodes(void)
{
	mNodes = new Node[WIDTH * HEIGHT];
	
	//init positions
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			mNodes[j * WIDTH + i].x = i;
			mNodes[j * WIDTH + i].y = j;
		}
	}

	//init neighbours
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (j > 0)
				mNodes[j * WIDTH + i].neighbours.push_back(&mNodes[(j - 1) * WIDTH + i]);
			if (j < HEIGHT - 1)
				mNodes[j * WIDTH + i].neighbours.push_back(&mNodes[(j + 1) * WIDTH + i]);
			if (i > 0)
				mNodes[j * WIDTH + i].neighbours.push_back(&mNodes[j * WIDTH + (i - 1)]);
			if (i < WIDTH - 1)
				mNodes[j * WIDTH + i].neighbours.push_back(&mNodes[j * WIDTH + (i + 1)]);
			
			if (j>0 && i>0)
				mNodes[j * WIDTH + i].neighbours.push_back(&mNodes[(j - 1) * WIDTH + (i - 1)]);
			if (j< HEIGHT -1 && i>0)
				mNodes[j* WIDTH + i].neighbours.push_back(&mNodes[(j + 1) * WIDTH + (i - 1)]);
			if (j>0 && i< WIDTH -1)
				mNodes[j* WIDTH + i].neighbours.push_back(&mNodes[(j - 1) * WIDTH + (i + 1)]);
			if (j< HEIGHT - 1 && i< WIDTH -1)
				mNodes[j* WIDTH + i].neighbours.push_back(&mNodes[(j + 1) * WIDTH + (i + 1)]);
		}
	}

	return true;
}

Graph::Graph(uint8_t width, uint8_t height, Context context)
	:	WIDTH(width),
		HEIGHT(height),
		mContext(context)
{
	init_nodes();
}

void Graph::update_graph(const vec2i& coord)
{
	mNodes[coord.x * WIDTH + coord.y].obstacle = (mNodes[coord.x * WIDTH + coord.y].obstacle == true) ? false : true;
	
}

Node* Graph::get_nodes(void) const
{
	return mNodes;
}
