#ifndef FORECAST_
#define FORECAST_

#include <nav_msgs/msg/occupancy_grid.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include "obstacle_forecaster/map.h"
#include <queue>
/*
#include "Action.h"
#include <std_msgs/msg/u_int32_multi_array.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include "State.h"
#include "SweepWorkerStatus.h"
#include <nav_msgs/msg/occupancy_grid.hpp>
#include "rclcpp/rclcpp.hpp"
#include <grid_map_msgs/srv/get_grid_map.hpp>
*/

using sensor_msgs::msg::LaserScan;

namespace obstacle_forecaster
{

class Forecaster {
public:
	Forecaster();
	bool setMaskMap(nav_msgs::msg::OccupancyGrid &map);
	void scanToMap(const LaserScan::ConstSharedPtr msg);
	void setParam(int skip_cycle);

private:
	Map mask_map_;
	std::queue<Map> maps_;
	int skip_cycle_;
};

}

#endif
