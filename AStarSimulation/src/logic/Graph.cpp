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

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mIsVisible)
	{
		sf::RectangleShape rec,conn;
		rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::NODE));
		rec.setSize(vec2f(32, 32));
		conn.setTexture(&mContext.mTextures->get_resource(Textures::ID::CONNECTION));
		//conn.setSize(36, 4);

		for (int x = 0; x < WIDTH; x++)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				if (mNodes[y * WIDTH + x].obstacle == false)
				{
					rec.setPosition((float)(x * 64 + 16), (float)(y * 64 + 16));
					target.draw(rec);

					for (auto node : mNodes[y * WIDTH + x].neighbours)
					{
						//conn.setPosition((float)(x * 64 + 16), (float)(y * 64 + 16));
						sf::Vertex line[] = { sf::Vertex(vec2f((float)(x * 64 + 64 / 2),(float)(y * 64 + 64 / 2))),sf::Vertex(vec2f((float)(node->x * 64 + 64 / 2),(float)(node->y * 64 + 64 / 2))) };
						target.draw(line, 2, sf::Lines);
					}
				}
			}
		}
	}
}

void Graph::update_graph(const vec2i& coord)
{
	mNodes[coord.x * WIDTH + coord.y].obstacle = (mNodes[coord.x * WIDTH + coord.y].obstacle == true) ? false : true;
	
	Node* nodeToUpdate = &mNodes[coord.x * WIDTH + coord.y];

	if (nodeToUpdate->obstacle)
	{
		for (auto node : nodeToUpdate->neighbours)
		{
			//node->neighbours.erase(std::remove(node->neighbours.begin(), node->neighbours.end(), &nodeToUpdate),node->neighbours.end());
			node->neighbours.clear();

		}
		nodeToUpdate->neighbours.clear();

		/*
		if (coord.x > 0)
			mNodes[coord.x * mWidth + coord.x].neighbours.push_back(&mNodes[(coord.x - 1) * mWidth + coord.x]);
		if (coord.x < mHeight - 1)
			mNodes[coord.x * mWidth + coord.x].neighbours.push_back(&mNodes[(coord.x + 1) * mWidth + coord.x]);
		if (coord.x > 0)
			mNodes[coord.x * mWidth + coord.x].neighbours.push_back(&mNodes[coord.x * mWidth + (coord.x - 1)]);
		if (coord.x < mWidth - 1)
			mNodes[coord.x * mWidth + coord.x].neighbours.push_back(&mNodes[coord.x * mWidth + (coord.x + 1)]);
		*/
	}
	else
	{
		
	}
}

void Graph::show_graph(void)
{
	mIsVisible = true;
}

void Graph::hide_graph(void)
{
	mIsVisible = false;
}

bool Graph::get_visibility(void) const
{
	return mIsVisible;
}

Node* Graph::get_nodes(void) const
{
	return mNodes;
}
