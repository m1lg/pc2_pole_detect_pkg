#include <ros/ros.h>
// PCL specific includes
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/voxel_grid.h>
#include <pointcloud_to_laserscan/pointcloud_to_laserscan_nodelet.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <array>
#include <sensor_msgs/LaserScan.h>

ros::Publisher pub;

void cloud_cb(const pcl::PCLPointCloud2ConstPtr& cloud) {
    pcl::PCLPointCloud2 cloud_filtered;
    
    
    // Perform the actual filtering
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud (cloud);
    sor.setLeafSize (0.4, 0.4, 0.4);
    sor.filter (cloud_filtered);

    ROS_INFO("print");
    // Publish the data
    pub.publish (cloud_filtered);
}

void scan_cb(const sensor_msgs::LaserScan::ConstPtr& msg) {
    
    uint16 i;
    ROS_INFO("ranges.size = %d", msg->ranges.size());
    for (i=0; i < msg->ranges.size(); i++) {
        
    }
}

int main (int argc, char** argv) {
    // Initialize ROS
    ros::init (argc, argv, "my_pcl_tutorial");
    ros::NodeHandle nh;

    // Create a ROS subscriber for the input point cloud
    ros::Subscriber sub_cloud = nh.subscribe("velodyne/front/filtered", 1, cloud_cb);
    ros::Subscriber sub_scan = nh.subscribe("camera/scan", 100, scan_cb);
    // Create a ROS publisher for the output point cloud
    pub = nh.advertise<pcl::PCLPointCloud2> ("output", 1);

    // Spin
    ros::spin ();
}
