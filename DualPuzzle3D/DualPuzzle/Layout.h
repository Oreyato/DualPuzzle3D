#pragma once
#include <vector>

#include "Vector3.h"
#include "Vector2.h"

struct Layout
{
	Layout() : 
		number{ 0 },
		description{ std::vector<int> { 0 } },
		rowNb{ 0 },
		colNb{ 0 },
		size{ 0 }
	{};

	Layout(int numP, std::vector<int> descP, int rowNbP, int colNbP) :
		number{ numP },
		description{ descP },
		rowNb{ rowNbP },
		colNb{ colNbP }
	{
		size = rowNb * colNb;
	};

	int number;
	std::vector<int> description;
	int rowNb;
	int colNb;
	int size;

	int worldCoordinatesToIndex(Vector3 worldCoordinates);
};


