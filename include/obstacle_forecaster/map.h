#ifndef MAP_ 
#define MAP_

#include <vector>

namespace obstacle_forecaster
{

class Map {
public:
	Map();
	int cell_num_x_;
	int cell_num_y_;
	double xy_resolution_;

	double origin_x_;
	double origin_y_;

	std::vector<int> data_;
};

}

#endif
