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
		mask_map_.data_.push_back(map.data[i]);
	}

	RCUTILS_LOG_INFO("READ MAP");
	RCUTILS_LOG_INFO("RESOLUTION: %lf", mask_map_.xy_resolution_);

	int step = mask_map_.cell_num_y_ / 30;
	for(int y=0; y<mask_map_.cell_num_y_; y+=step) {
		for(int x=0; x<mask_map_.cell_num_x_; x+=step) {
			std::cerr << mask_map_.data_[x + (mask_map_.cell_num_y_ - y - 1)*mask_map_.cell_num_x_] << " ";
		}
		std::cerr << std::endl;
	}

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
		return;
	}
	counter++;

	Map m = mask_map_.makeBlankMap();

	double start_angle = msg->angle_min;
	for(unsigned long int i=0; i<msg->ranges.size(); i++){
		double a = msg->angle_increment*i + start_angle;

		double lx = msg->ranges[i]*cos(a);
		double ly = msg->ranges[i]*sin(a);
        	int ix = (int)floor( (lx - m.origin_x_)/m.xy_resolution_ );
        	int iy = (int)floor( (ly - m.origin_y_)/m.xy_resolution_ );

	/*
		for(double d=0.1;d<=0.9;d+=0.1){
			double half_lx = x + msg->ranges[i]*cos(a)*d;
			double half_ly = y + msg->ranges[i]*sin(a)*d;
	        	int half_ix = (int)floor( (half_lx - map_origin_x_)/xy_resolution_ );
	        	int half_iy = (int)floor( (half_ly - map_origin_y_)/xy_resolution_ );
	
			if(not inLocalArea(half_ix, half_iy))
				continue;
			
			for(int it=0;it<cell_num_t_;it++){
				int index = toIndex(half_ix, half_iy, it);
				states_[index].local_penalty_ /= 2;
			}
		}

		for(int iix=ix-2;iix<=ix+2;iix++){
			for(int iiy=iy-2;iiy<=iy+2;iiy++){

				if(not inLocalArea(iix, iiy))
					continue;

				for(int it=0;it<cell_num_t_;it++){
					int index = toIndex(iix, iiy, it);
					states_[index].local_penalty_ = 2048 << prob_base_bit_;
				}
			}
		}*/

	}
}

}
