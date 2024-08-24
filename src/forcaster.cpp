#include <chrono>
#include <fstream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int16_multi_array.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>

using namespace std::chrono_literals;
using sensor_msgs::msg::LaserScan;

namespace obstacle_forcaster
{

class Forcaster : public rclcpp::Node
{
public:
	Forcaster() : Node("forecaster") 
	{
		scan_ = create_subscription<LaserScan>(
	  		"scan", 2, std::bind(&Forcaster::receiveScan, this, std::placeholders::_1));

		publisher_ = create_publisher<std_msgs::msg::Int16MultiArray>("futureobs", 10);
		timer_ = create_wall_timer(100ms, std::bind(&Forcaster::timer_callback, this));
	}

private:
	rclcpp::Publisher<std_msgs::msg::Int16MultiArray>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_;

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

