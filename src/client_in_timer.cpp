#include <rclcpp/executors.hpp>
#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>
#include <iostream>

class ThingDoer {
public:
    ThingDoer(const std::shared_ptr<rclcpp::Node>& node)
    : client_cb_group_{node->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive)}
    , timer_cb_group_{node->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive)}
    , client_{node->create_client<example_interfaces::srv::AddTwoInts>("/add_two_ints", rmw_qos_profile_services_default, client_cb_group_)}
    , timer_{ node->create_wall_timer(std::chrono::seconds(1), [=]{ timerCallback();}, timer_cb_group_)}
    {}

private:
    void timerCallback()
    {
        std::cout << "In timer callback" << std::endl;

        const auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = 1;
        request->b = 2;

        auto result_future = client_->async_send_request(request);

        if (result_future.wait_for(std::chrono::seconds(3)) == std::future_status::timeout)
        {
            std::cout << "Timed out!" << std::endl;
            return;
        }

        auto result = result_future.get();
        std::cout << "The sum is: " << result->sum << std::endl;
    }

    std::shared_ptr<rclcpp::CallbackGroup> client_cb_group_;
    std::shared_ptr<rclcpp::CallbackGroup> timer_cb_group_;

    std::shared_ptr<rclcpp::Client<example_interfaces::srv::AddTwoInts>> client_;
    std::shared_ptr<rclcpp::TimerBase> timer_;
};



int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    rclcpp::init(argc, argv);

    const auto node = std::make_shared<rclcpp::Node>("my_node");
    ThingDoer thing_doer(node);

    rclcpp::executors::MultiThreadedExecutor exec;
    exec.add_node(node);
    exec.spin();

    rclcpp::shutdown();
}
