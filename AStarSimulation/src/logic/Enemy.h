#pragma once

#include "../states/State.h"

class Graph;
class PathFinder;
typedef States::State::Context Context;

class Enemy
{
private:
	Context mContext;
	Animation* mAnimation;
	PathFinder* mPathFinder;

public:
	Enemy();
};