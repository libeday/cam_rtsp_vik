#include "cam_rtsp_vik/cam_receiver.h"

CamReceiver::CamReceiver() {
  color_topic = "toColorTopic";
  depth_topic = "toDepthTopic";
  ir_topic = "toIrTopic";

  ros::param::get("/_color_topic", color_topic);
  ros::param::get("/_depth_topic",   depth_topic);
  ros::param::get("/_ir_topic",   ir_topic);

  m_get_color = false;
  m_get_depth = false;
  m_get_ir = false;

  color_sub = _node.subscribe(color_topic, 1, &CamReceiver::colorCallback, this);
  depth_sub = _node.subscribe(depth_topic, 1, &CamReceiver::depthCallback, this);
  ir_sub = _node.subscribe(ir_topic, 1, &CamReceiver::irCallback, this);

}
void CamReceiver::start () {
  std::cout << "CAM RECEIVER IS RUNNING\n";
  ros::spin();
};

void CamReceiver::colorCallback(const sensor_msgs::Image::ConstPtr& msg) {
  
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  
  curr_color_img = cv_ptr->image;
  m_get_color = true;
  cv::imshow("COLOR_CHL", cv_ptr->image);
  cv::waitKey(3);
  
}

void CamReceiver::depthCallback(const sensor_msgs::Image::ConstPtr& msg) {
  m_get_depth = true;
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO16);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  curr_depth_img = cv_ptr->image;
  m_get_depth = true;
  cv::imshow("DEPTH_CHL", cv_ptr->image);
  cv::waitKey(3);
}

void CamReceiver::irCallback(const sensor_msgs::Image::ConstPtr& msg) {
  m_get_ir = true;
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  curr_ir_img = cv_ptr->image;
  m_get_ir = true;
  cv::imshow("IR_CHL", cv_ptr->image);
  cv::waitKey(3);
}

void ethCallback(const std_msgs::ByteMultiArray::ConstPtr& msg) {
  std::cout << "get bytes!\n";
}