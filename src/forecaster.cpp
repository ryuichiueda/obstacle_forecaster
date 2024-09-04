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

	RCUTILS_LOG_INFO("READ MAP");

	mask_map_.cell_num_x_ = map.info.width;
	mask_map_.cell_num_y_ = map.info.height;

	mask_map_.xy_resolution_ = map.info.resolution;
	/*
	t_resolution_ = 360/cell_num_t_;
	RCUTILS_LOG_INFO("GLOBAL: %lf %lf", map.info.resolution, xy_resolution_);

	map_origin_x_ = map.info.origin.position.x;
	map_origin_y_ = map.info.origin.position.y;
	map_origin_quat_ = map.info.origin.orientation;

	RCUTILS_LOG_INFO("SET STATES START");
	setState(map, safety_radius, safety_radius_penalty);
	setStateTransition();
	setSweepOrders();
	RCUTILS_LOG_INFO("SET STATES END");

	*/
	return true;
}


//void scanToMap(const sensor_msgs::msg::LaserScan::ConstSharedPtr msg, double x, double y, double t)
void Forecaster::scanToMap(const LaserScan::ConstSharedPtr msg)
{
	double start_angle = msg->angle_min;
	/*
	for(unsigned long int i=0; i<msg->ranges.size(); i++){
		double a = t + msg->angle_increment*i + start_angle;

		double lx = x + msg->ranges[i]*cos(a);
		double ly = y + msg->ranges[i]*sin(a);
        	int ix = (int)floor( (lx - map_origin_x_)/xy_resolution_ );
        	int iy = (int)floor( (ly - map_origin_y_)/xy_resolution_ );

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
		}

	}*/
}

}
