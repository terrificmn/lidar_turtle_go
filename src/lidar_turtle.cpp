/// 다른 패키지의 msg 를 가져오는 예제 
/// publisher와 subscriber 를 동시에 활용
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
//#include <turtlesim/TeleportAbsolute.h>
//#include <std_srvs/Empty.h>
#include <sensor_msgs/LaserScan.h>
#include <visualization_msgs/MarkerArray.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ros::Publisher pub; //전역으로 선언

//void msgCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {}
void msgCallback(const visualization_msgs::MarkerArray::ConstPtr &msg) {
    
    const double PI = 3.1415;
    //cout << "X: " << msg->markers[1].pose.position.x << endl;
    //cout << "Y: " << msg->markers[1].pose.position.y << endl;
    //cout << "Z: " << msg->markers[1].pose.position.z << endl;

    geometry_msgs::Twist moveTur;

    int markersSize = msg->markers.size();
    double turtleMinusMinX = 0;
    double turtlePlusMinX = 0;
    double turtlePlusTmp = 0;

    //turtleMinusMinX = msg->markers[0].pose.position.x;
    //turtlePlusMinX = msg->markers[0].pose.position.x;
    
    vector<double> xPlusTemp(markersSize);
    vector<double> xMinusTemp(markersSize);

    const double MAX_TRIANGLG_DIST = 625.0; // 라이다 최대치  25 X 25
    double minDistance = 0.0;
    double minX = 0;
    double minY = 0;

    for (int i =0; i < markersSize; i++) {

        if (msg->markers[i].type == 2) {    //shape가 2번 // object선택되었을 시
    
            //cout << msg->markers[i].type << "으갸갸갸ㅑㄱ" << endl;
            double comparison = (msg->markers[i].pose.position.x * msg->markers[i].pose.position.x) + (msg->markers[i].pose.position.y * msg->markers[i].pose.position.y);
            
            if( MAX_TRIANGLG_DIST > comparison ) {
                
                minDistance = comparison;
                minX = msg->markers[i].pose.position.x;
                minY = msg->markers[i].pose.position.y;
            }

        }
        
    } 

    if (minDistance != 0 && minDistance > 0) {
        cout << "최소값 : " << minDistance << endl;
        cout << "x : " << minX << endl;
        cout << "y : " << minY << endl;

        moveTur.linear.x = minX /100;
        moveTur.linear.y = minY /100;
        
    }else {
        moveTur.linear.x = -(minX /100);
        moveTur.linear.y = -(minY /100);
    }

    // 처음에 for문을 돌때 size가 0인 경우도 있어서 위에 선언된 그대로 입력이 되어서 0 이 들어감
    //turtlePlusMinX = *min_element(xPlusTemp.begin(), xPlusTemp.end());   //#include <algorithm> 필요
    // turtleMinusMinX = *min_element(xMinusTemp.begin(), xMinusTemp.end());   //#include <algorithm> 필요
    //std::cout << "x 플러스 최소값 : " << turtlePlusMinX << std::endl;
    // std::cout << "x 마이너스 최소값 : " << turtleMinusMinX << std::endl;

    // cout << "작은? plus 물체 x: " << turtlePlusMinX << endl;
    // cout << "작은? minus 물체 x: " << turtleMinusMinX << endl;



    // y축 움직이기 시도
    // double tempY = 0.0; 
    // if (msg->markers[1].pose.position.x < -0.7 && msg->markers[1].pose.position.x > -8.325) {
    //     moveTur.linear.x = 0.2; //속도 셋팅
    //     tempY = msg->markers[1].pose.position.y;

    //     if (tempY > msg->markers[1].pose.position.y) {
    //         moveTur.linear.y =  msg->markers[1].pose.position.y;
    //     } else if (tempY < msg->markers[1].pose.position.y) {
    //         moveTur.linear.x = 0;
    //         moveTur.angular.z = PI / 2;
    //         cout << "벽쪽으로 움직여" << endl;
    //     }
    //     moveTur.linear.y = msg->markers[1].pose.position.y;

        
    //     cout << "detected Y: " << msg->markers[1].pose.position.y << endl;
        
    // } else if (msg->markers[1].pose.position.x > 0) {
    //     moveTur.linear.x = 0;
    //     moveTur.angular.z = 0;
    // }

    
    // cout << msg->linear.z;
    // cout << "+++++++++++++++++++++++++";

    pub.publish(moveTur);
    
    

}


// void msgTurtleCallback(const geometry_msgs::Twist::ConstPtr &msg) {
    
//     cout << "msg->angular.x " << msg->angular.x << endl;
//     cout << "msg->angular.y " << msg->angular.y << endl;
//     cout << "msg->angular.z " << msg->angular.z << endl;
//     cout << "----------------------------------------\n";
//     cout << "msg->linear.x " << msg->linear.x << endl;
//     cout << "msg->linear.y " << msg->linear.y << endl;
//     cout << "msg->linear.z " << msg->linear.z << endl;
    
    

// }


int main (int argc, char** argv) {
    ros::init(argc, argv, "Lidar_turtle_go");
    ros::NodeHandle nh;

    //ros::Subscriber subLidar = nh.subscribe("/raw_lidar", 100, msgCallback);
    ros::Subscriber subLidar = nh.subscribe("/marker_array", 100, msgCallback);

    //ros::Subscriber sub = nh.subscribe("/cmd_vel", 10, msgCallback);
    pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100); //publisher
    ros::spin();

    return 0;
}