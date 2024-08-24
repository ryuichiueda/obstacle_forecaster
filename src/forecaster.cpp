#include <chrono>
#include <fstream>
#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/int16_multi_array.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <nav_msgs/srv/get_map.hpp>

using namespace std::chrono_literals;
using sensor_msgs::msg::LaserScan;

namespace obstacle_forcaster
{

class Forcaster : public rclcpp::Node
{
public:
	Forcaster() : Node("forecaster") 
	{
		while (true) {
			auto client = create_client<nav_msgs::srv::GetMap>("/map_server/map");
			while (!client->wait_for_service(1s)) {
				if (!rclcpp::ok()) {
					RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for map.");
					return;
				}
				RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "map server not available, waiting again...");
			}
		
			auto req = std::make_shared<nav_msgs::srv::GetMap::Request>();
			auto res = client->async_send_request(req);
			
			if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), res) 
					== rclcpp::FutureReturnCode::SUCCESS) {
			/*
				if (vi_->setMapWithOccupancyGrid(res.get()->map,
					theta_cell_num, safety_radius, safety_radius_penalty,
					goal_margin_radius, goal_margin_theta)) {
					break;
				}
		*/
			} else {
				RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call map service");
			}
			sleep(1);
		}

		scan_ = create_subscription<LaserScan>(
	  		"scan", 2, std::bind(&Forcaster::receiveScan, this, std::placeholders::_1));

		publisher_ = create_publisher<std_msgs::msg::Int16MultiArray>("futureobs", 10);
		timer_ = create_wall_timer(100ms, std::bind(&Forcaster::timer_callback, this));
	}

private:
	rclcpp::Publisher<std_msgs::msg::Int16MultiArray>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Subscription<LaserScan>::SharedPtr scan_;

	void receiveScan(const LaserScan::ConstSharedPtr msg)
	{
	}

	void timer_callback()
	{
		auto message = std_msgs::msg::Int16MultiArray();
		for(int i=0;i<4;i++){
			message.data.push_back(i);
		}
		publisher_->publish(message);
	}
};

}

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<obstacle_forcaster::Forcaster>());
	rclcpp::shutdown();
	return 0;
}

