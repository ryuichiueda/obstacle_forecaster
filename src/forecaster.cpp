#include "obstacle_forecaster/forecaster.h"
#include <rclcpp/rclcpp.hpp>
#include "obstacle_forecaster/map.h"

namespace obstacle_forecaster {

Forecaster::Forecaster(){
}

bool Forecaster::setMaskMap(nav_msgs::msg::OccupancyGrid &map)
{
	if ( map.info.width <= 0 || map.info.height <= 0 || map.info.resolution < 0.0001 )
		return false;

	mask_map_.cell_num_x_ = map.info.width;
	mask_map_.cell_num_y_ = map.info.height;

	mask_map_.xy_resolution_ = map.info.resolution;

	mask_map_.origin_x_ = map.info.origin.position.x;
	mask_map_.origin_y_ = map.info.origin.position.y;

	for(int i=0; i<mask_map_.cell_num_x_*mask_map_.cell_num_y_; i++) {
		int iy = mask_map_.cell_num_y_ - i/mask_map_.cell_num_y_ - 1;
		int ix = i%mask_map_.cell_num_y_;
		mask_map_.data_.push_back(map.data[mask_map_.xyToIndex(ix, iy)]);
	}

	RCUTILS_LOG_INFO("READ MAP");
	RCUTILS_LOG_INFO("RESOLUTION: %lf", mask_map_.xy_resolution_);

	mask_map_.eprint();

	return true;
}

void Forecaster::setParam(int skip_cycle) {
	skip_cycle_ = skip_cycle;
	std::cerr << "SKIP CYCLE: " << skip_cycle_ << std::endl;
}

void Forecaster::scanToMap(const LaserScan::ConstSharedPtr msg)
{
	static uint64_t counter = 0;
	if(counter%skip_cycle_ != 0) {
		counter++;
		return;
	}
	counter++;

	Map m = mask_map_.makeBlankMap();

	double start_angle = msg->angle_min;
	for(unsigned long int i=0; i<msg->ranges.size(); i++){
		double a = msg->angle_increment*i + start_angle + 3.151592/2;

		double lx = msg->ranges[i]*cos(a);
		double ly = msg->ranges[i]*sin(a);
        	int ix = (int)floor( (lx - m.origin_x_)/m.xy_resolution_ );
        	int iy = (int)floor( (ly - m.origin_y_)/m.xy_resolution_ );

		/*
		std::cerr << "angle:" << a/3.141592*180 << " x:" << lx << " y:" << ly << std::endl;
		std::cerr << "ix:" << ix << " iy:" << iy << std::endl;
		*/

		int index = m.xyToIndex(ix, iy);

		if(index < 0)
			continue;

		m.data_[index] = 255;
	}

	m.eprint();
	std::cerr << std::endl;
}

}
