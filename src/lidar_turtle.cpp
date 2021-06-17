/// 다른 패키지의 msg 를 가져오는 예제 
/// publisher와 subscriber 를 동시에 활용
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
//#include <turtlesim/TeleportAbsolute.h>
//#include <std_srvs/Empty.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
using namespace std;

ros::Publisher pub; //전역으로 선언
int inputLength = 0;  // 사용자 거리 입력

void msgCallback(const geometry_msgs::Twist::ConstPtr &msg) {
    cout << "hey inside" << endl;

    //msg.
}

int main (int argc, char** argv) {
    ros::init(argc, argv, "Lidar_turtle_go");
    ros::NodeHandle nh;

    ros::Subscriber subLidar = nh.subscribe("/raw_lidar", 100, msgCallback);
    
    // /clear 서비스 클라이언트 호출해서 처음에 선 지우기
    // 먼저 turtlesim 켜져있는 상태에서 rosservice list 해보면 그 중에 /clear 란 서비스가 있고
    // rosservice info /clear 를 해보면 타입은 Type: std_srvs/Empty 라고 나온다 
    // 이를 이용해서 핸들러를 이용해서 serviceClient를 지정해주고 std_srvs::Empty /clear가 서비스명이다
    // ros::ServiceClient clearSrv = nh.serviceClient<std_srvs::Empty>("/clear");
    // std_srvs::Empty clearCall;
    // clearSrv.call(clearCall);

    pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100); //publisher
    ros::spin();

    return 0;
}