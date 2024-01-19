// #pragma once

#include <iostream>
#include <ros/ros.h>
#include "sensor_msgs/Image.h"

#include "cam_rtsp_vik/cam_receiver.h"


int main(int argc, char** argv) {
    ros::init(argc, argv, "cam_receiver");
    CamReceiver receiver;
    receiver.start();
    
    return 0;

}