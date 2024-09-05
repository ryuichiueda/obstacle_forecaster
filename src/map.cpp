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

int Map::xyToIndex(int x, int y) {
	if (x < 0 || x >= cell_num_x_) {
		return -10000;
	}
	if (y < 0 || y >= cell_num_y_) {
		return -10000;
	}

	return x + (cell_num_y_ - y - 1)*cell_num_x_;
}


}

//			std::cerr << mask_map_.data_[x + (mask_map_.cell_num_y_ - y - 1)*mask_map_.cell_num_x_] << " ";
