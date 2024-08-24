#include <chrono>
#include <fstream>
#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/int16_multi_array.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <nav_msgs/srv/get_map.hpp>
#include "obstacle_forecaster/forecaster.h"

using namespace std::chrono_literals;
using sensor_msgs::msg::LaserScan;
using rclcpp::FutureReturnCode;

namespace obstacle_forecaster
{

class ForecasterNode : public rclcpp::Node
{
public:
	ForecasterNode();

private:
	rclcpp::Publisher<std_msgs::msg::Int16MultiArray>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Subscription<LaserScan>::SharedPtr scan_;
	Forecaster forecaster_;

	void receiveScan(const LaserScan::ConstSharedPtr msg);
	void timerCallback();
	void waitAndReadMaskMap(void);
};

ForecasterNode::ForecasterNode() : Node("forecaster") 
{
	waitAndReadMaskMap();
	scan_ = create_subscription<LaserScan>(
  		"scan", 2, std::bind(&ForecasterNode::receiveScan, this, std::placeholders::_1));

	publisher_ = create_publisher<std_msgs::msg::Int16MultiArray>("futureobs", 10);
	timer_ = create_wall_timer(100ms, std::bind(&ForecasterNode::timerCallback, this));
}

void ForecasterNode::waitAndReadMaskMap(void) {
	while (true) {
		auto client = create_client<nav_msgs::srv::GetMap>("/map_server/map");
		while (!client->wait_for_service(1s)) {
			if (!rclcpp::ok()) {
				RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for map.");
				exit(1);
			}
			RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "map server not available, waiting again...");
		}
	
		auto req = std::make_shared<nav_msgs::srv::GetMap::Request>();
		auto res = client->async_send_request(req);
		
		if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), res) == FutureReturnCode::SUCCESS) {
			if (forecaster_.setMaskMap(res.get()->map))
				break;
		} else {
			RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call map service");
			exit(1);
		}

		sleep(1);
	}
}

void ForecasterNode::receiveScan(const LaserScan::ConstSharedPtr msg)
{
}

void ForecasterNode::timerCallback()
{
	auto message = std_msgs::msg::Int16MultiArray();
	for(int i=0;i<4;i++){
		message.data.push_back(i);
	}
	publisher_->publish(message);
}

}

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<obstacle_forecaster::ForecasterNode>());
	rclcpp::shutdown();
	return 0;
}

