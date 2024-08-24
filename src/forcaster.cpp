#include <chrono>
#include <fstream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int16_multi_array.hpp"

using namespace std::chrono_literals;

namespace obstacle_forcaster
{

class Forcaster : public rclcpp::Node
{
public:
	Forcaster() : Node("futureobs") 
	{
		publisher_ = create_publisher<std_msgs::msg::Int16MultiArray>("futureobs", 10);
		timer_ = create_wall_timer(100ms, std::bind(&Forcaster::timer_callback, this));
	}

private:
	void timer_callback()
	{
		auto message = std_msgs::msg::Int16MultiArray();
		std::ifstream ifs("/dev/rtlightsensor0");
		int16_t value;
		for(int i=0;i<4;i++){
			ifs >> value;
			message.data.push_back(value);
		}
		publisher_->publish(message);
	}

	rclcpp::Publisher<std_msgs::msg::Int16MultiArray>::SharedPtr publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
};

}

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<obstacle_forcaster::Forcaster>());
	rclcpp::shutdown();
	return 0;
}

