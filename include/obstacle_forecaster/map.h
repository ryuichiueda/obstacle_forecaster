#ifndef MAP_ 
#define MAP_

using sensor_msgs::msg::LaserScan;

namespace obstacle_forecaster
{

class Map {
public:
	Map(){}
	int cell_num_x_;
	int cell_num_y_;
	double xy_resolution_;
};

}

#endif
