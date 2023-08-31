#include <chrono>
#include <thread>

#include <basic/basic.h>

namespace smov {

void BasicState::on_start() {

  // Some sample configuration.
  set_all_servos_to(1.0f);
  set_front_servo_to(LEFT_BICEPS, 0.0f);
  set_back_servo_to(LEFT_BICEPS, 0.0f);
  set_front_servo_to(RIGHT_BICEPS, 0.0f);
  set_back_servo_to(RIGHT_BICEPS, 0.0f);
}

void BasicState::on_loop() {}

void BasicState::on_quit() {}

void BasicState::set_back_servo_to(RobotParts part, float value) {
  if (value > 1.0f || value < -1.0f) {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Value selected is not inside I = [-1.0;1.0], [value=%f].", value);
    return;
  }
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Setting back servo number %d to [value=%f].", part, value);

  back_servos.value[part] = value; 
  back_state_publisher->publish(back_servos);
}

void BasicState::set_front_servo_to(RobotParts part, float value) {
  if (value > 1.0f || value < -1.0f) {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Value selected is not inside I = [-1.0;1.0], [value=%f].", value);
    return;
  }
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Setting front servo number %d to [value=%f].", part, value);

  front_servos.value[part] = value; 
  front_state_publisher->publish(front_servos);
}

void BasicState::set_all_servos_to(float value) {
  if (value > 1.0f || value < -1.0f) {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Value selected is not inside I = [-1.0;1.0], [value=%f].", value);
    return;
  }
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Setting front & back servos to [value=%f].", value);

  // Taking the values from the YAML file.
  for (int i = 0; i < SERVO_MAX_SIZE; i++) {
    front_servos.value[i] = value; 
    back_servos.value[i] = value;
  }

  front_state_publisher->publish(front_servos);
  back_state_publisher->publish(back_servos);
}

void BasicState::set_all_servos_to_center() {
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Setting front & back servos to center [value=0].");

  // Taking the values from the YAML file.
  for (int i = 0; i < SERVO_MAX_SIZE; i++) {
    front_servos.value[i] = 0.0f; 
    back_servos.value[i] = 0.0f;
  }

  front_state_publisher->publish(front_servos);
  back_state_publisher->publish(back_servos);
}

void BasicState::set_all_servos_to_min() {
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Setting front & back servos to minimum value.");

  for (int i = 0; i < SERVO_MAX_SIZE; i++) {
    front_servos.value[i] = -1.0f; 
    back_servos.value[i] = -1.0f;
  }

  front_state_publisher->publish(front_servos);
  back_state_publisher->publish(back_servos);
}

void BasicState::set_all_servos_to_max() {
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Setting front & back servos to maximum value.");

  for (int i = 0; i < SERVO_MAX_SIZE; i++) {
    front_servos.value[i] = 1.0f;
    back_servos.value[i] = 1.0f;
  }

  front_state_publisher->publish(front_servos);
  back_state_publisher->publish(back_servos);
}

}

DECLARE_STATE_NODE_CLASS("smov_basic_state", smov::BasicState, 100ms)
