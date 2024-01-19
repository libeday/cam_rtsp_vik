#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/ByteMultiArray.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class CamReceiver
{
public:
    
    ros::Subscriber depth_sub;
    ros::Subscriber ir_sub;
    ros::Subscriber color_sub;

    ros::Subscriber eth_vik_sub;

    std::string color_topic;
    std::string depth_topic;
    std::string ir_topic;

    cv::Mat curr_color_img;
    cv::Mat curr_depth_img;
    cv::Mat curr_ir_img;

    CamReceiver();
    void start ();

    
private:
    ros::NodeHandle _node;  
    void colorCallback(const sensor_msgs::Image::ConstPtr& msg);
    void depthCallback(const sensor_msgs::Image::ConstPtr& msg);
    void irCallback(const sensor_msgs::Image::ConstPtr& msg);
    void ethCallback(const std_msgs::ByteMultiArray::ConstPtr& msg);
    
    bool m_get_color;
    bool m_get_depth;
    bool m_get_ir;
};