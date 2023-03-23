#pragma once
#include <vector>


struct Layout
{
	Layout() = delete;
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
};

