#include "pch.h"
#include "Graph.h"
#include "../res/ResourceManager.h"


bool Graph::init_nodes(void)
{
	mNodes = new Node[mWidth * mHeight];
	
	//init positions
	for (int i = 0; i < mWidth; i++)
	{
		for (int j = 0; j < mHeight; j++)
		{
			mNodes[j * mWidth + i].x = i;
			mNodes[j * mWidth + i].y = j;
		}
	}

	//init neighbours
	for (int i = 0; i < mWidth; i++)
	{
		for (int j = 0; j < mHeight; j++)
		{
			if (j > 0)
				mNodes[j * mWidth + i].neighbours.push_back(&mNodes[(j - 1) * mWidth + i]);
			if (j < mHeight - 1)
				mNodes[j * mWidth + i].neighbours.push_back(&mNodes[(j + 1) * mWidth + i]);
			if (i > 0)
				mNodes[j * mWidth + i].neighbours.push_back(&mNodes[j * mWidth + (i - 1)]);
			if (i < mWidth - 1)
				mNodes[j * mWidth + i].neighbours.push_back(&mNodes[j * mWidth + (i + 1)]);
		}
	}

	return true;
}

Graph::Graph(uint8_t width, uint8_t height, Context context)
	:	mWidth(width),
		mHeight(height),
		mContext(context)
{
	init_nodes();
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mIsVisible)
	{
		sf::RectangleShape rec;
		rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::NODE));
		rec.setSize(vec2f(32, 32));

		for (int x = 0; x < mWidth; x++)
		{
			for (int y = 0; y < mHeight; y++)
			{
				if (mNodes[y * mWidth + x].obstacle == false)
				{
					rec.setPosition((float)(x * 64 + 16), (float)(y * 64 + 16));
					target.draw(rec);
				}
			}
		}
	}
}

void Graph::update_graph(const vec2i& coord)
{
	mNodes[coord.x * mWidth + coord.y].obstacle = (mNodes[coord.x * mWidth + coord.y].obstacle == true) ? false : true;
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
