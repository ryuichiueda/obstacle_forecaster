#include "obstacle_forecaster/forecaster.h"
#include <rclcpp/rclcpp.hpp>

namespace obstacle_forecaster {

Forecaster::Forecaster(){
}

bool Forecaster::setMaskMap(nav_msgs::msg::OccupancyGrid &map)
{
	if ( map.info.width <= 0 || map.info.height <= 0 || map.info.resolution < 0.0001 )
		return false;

	RCUTILS_LOG_INFO("SET MAP");
	/*
	cell_num_t_ = theta_cell_num;
	goal_margin_radius_ = goal_margin_radius;
	goal_margin_theta_ = goal_margin_theta;

	cell_num_x_ = map.info.width;
	cell_num_y_ = map.info.height;

	xy_resolution_ = map.info.resolution;
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

}
