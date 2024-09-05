#include "obstacle_forecaster/map.h"

namespace obstacle_forecaster {

Map::Map()
{
}

Map Map::makeBlankMap(void)
{
	Map ret;
	ret.cell_num_x_ = cell_num_x_;
	ret.cell_num_y_ = cell_num_y_;
	ret.xy_resolution_ = xy_resolution_;

	ret.origin_x_ = origin_x_;
	ret.origin_y_ = origin_y_;
	
	ret.data_ = std::vector<int>(data_.size(), 0);

	return ret;
}

}
