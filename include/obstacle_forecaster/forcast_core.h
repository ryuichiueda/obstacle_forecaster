#ifndef FORECAST_CORE_
#define FORECAST_CORE_

#include <nav_msgs/msg/occupancy_grid.hpp>
/*
#include "Action.h"
#include <std_msgs/msg/u_int32_multi_array.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include "State.h"
#include "SweepWorkerStatus.h"
#include <map>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include "rclcpp/rclcpp.hpp"
#include <grid_map_msgs/srv/get_grid_map.hpp>
*/

namespace obstacle_forecaster
{

class ForecastCore {
public:
	ForecastCore();
	bool setMaskMap(nav_msgs::msg::OccupancyGrid &map);
	/*
protected: 
	std::vector<State> states_;
	std::vector<Action> &actions_;
	std::vector<std::vector<int> > sweep_orders_;
	uint64_t valueIteration(State &s);

	uint64_t actionCost(State &s, Action &a);
public:
	void setGoal(double goal_x, double goal_y, int goal_t);
	void valueIterationWorker(unsigned int times, int id);
protected: 
	int toIndex(int ix, int iy, int it);
	bool inMapArea(int ix, int iy);
	void cellDelta(double x, double y, double t, int &ix, int &iy, int &it);
	void noNoiseStateTransition(Action &a, double from_x, double from_y, double from_t, double &to_x, double &to_y, double &to_t);
	rclcpp::Clock ros_clock_;
public: 
	bool endOfTrial(void);
	//bool arrived(void);
	Action *posToAction(double x, double y, double t_rad);
	//void setCalculated(void);
	//bool isCalculated(void);

	void setMapWithCostGrid(nav_msgs::msg::OccupancyGrid &map, int theta_cell_num,
		double goal_margin_radius, int goal_margin_theta);
protected:
	void setStateValues(void);
	void setStateTransitionWorker(int it);
	void setStateTransitionWorkerSub(Action &a, int it);
	void setState(const nav_msgs::msg::OccupancyGrid &map, double safety_radius, double safety_radius_penalty);
	void setStateTransition(void);
	void setSweepOrders(void);

public:
	void makeValueFunctionMap(nav_msgs::msg::OccupancyGrid &map, int threshold, double yaw_rad);
	std::map<int, SweepWorkerStatus> thread_status_; 
	void setCancel(void);
	bool finished(std_msgs::msg::UInt32MultiArray &sweep_times, std_msgs::msg::Float32MultiArray &deltas);

	bool idling_;

public: 
	double goal_x_, goal_y_, goal_margin_radius_;
	int goal_t_, goal_margin_theta_;
	int thread_num_;
protected:
	double xy_resolution_, t_resolution_;
	int cell_num_x_, cell_num_y_, cell_num_t_;
	double map_origin_x_;
	double map_origin_y_;
	geometry_msgs::msg::Quaternion map_origin_quat_;
	const static unsigned char resolution_xy_bit_ = 6;
	const static unsigned char resolution_t_bit_ = 6;
public:
	const static unsigned char prob_base_bit_ = resolution_xy_bit_*2+resolution_t_bit_;
	const static uint64_t prob_base_ = 1<<prob_base_bit_;
	const static uint64_t max_cost_ = 1000000000*prob_base_;
	*/
};

}

#endif
