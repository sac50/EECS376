#include <math.h>
#include <ros/ros.h>
#include <cwru_base/Pose.h>
#include <sensor_msgs/LaserScan.h>
#include <beta_nodes/obstacle.h>
#include <iostream>
#include <beta_nodes/PathSegment.h>


#define CUTOFF 5 //disregard this many degrees of laser scan from the edges
#define HZ 100
#define PI 3.141562653589
#define D2R 0.0174532925 //pi/180
#define LISTENTOTHIS "base_scan" // "base_laser1_scan" for jinx

using namespace std;
float nearestObstacle;
int nearestTheta;
float leftClearance;
float rightClearance;
float edgeDistance;
int edgeTheta;
int firstObstacleTheta;
int lastObstacleTheta;
bool objectInRange = false;
bool holla = false;

// For using the LaserScan, see http://www.ros.org/doc/api/sensor_msgs/html/msg/LaserScan.html

//inDeBox tells if a point at a given theta and radial distance from the laser 
//lies in a rectrangular area infront of the robot, whose width and length are 
//defined for fun in the 'obstacle' message 
bool inDeBox(int theta, float r)
{

	beta_nodes::obstacle referenceMsg; //this is used to get the constants from the message
	bool result = false;

	if(abs(r*sin(theta*D2R))<referenceMsg.boxLength) //abs() hack for negative values ...
	{
		if(abs(r*cos(theta*D2R))<(referenceMsg.boxWidth))
		{
			//cout << "front: " << r*sin(theta*D2R) << "	side: " << r*cos(theta*D2R) << endl;			
			cout << "x";
			result = true;
		}
	}

	return result;
}

bool diff(float a, float b)
{
	float K = .05;
	if(a<b-K || a>b+K) //TODO: say what this does for us  
	{
		return false;
	}
	return true;
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& laserScan)
{
	objectInRange = false;
	nearestTheta = 0;
	edgeTheta = 0;
	firstObstacleTheta = 0;
	lastObstacleTheta = 0;
	float edgeDetectThreshold = .5;
	float shortestRange = 999.999;
	float jag;
	bool jagFlag = false;
	cout << "-=-=-=-=-=-=-= C A L L B A C K =-=-=-=-=-=-=-=-=-";

	rightClearance = laserScan->ranges[CUTOFF];
	leftClearance = laserScan->ranges[180-CUTOFF];

	for(uint i = CUTOFF; i < 180-CUTOFF; i++)
	{
	  if (laserScan->ranges[i]<shortestRange)
	  {
		  shortestRange = laserScan->ranges[i];
		  nearestTheta = i;
	  }

	  jag = abs(laserScan->ranges[i]-laserScan->ranges[i-1]); //NOTE: focusing on obstacle=s on our left 
	  if (jag > edgeDetectThreshold && !jagFlag)
	  {
			edgeDistance = laserScan->ranges[i];
			edgeTheta = i;  
			cout << "JAGGINESS@"<<i<<": " << jag << endl;
	  }
	  
	  //cout << inDeBox(i, laserScan->ranges[i]);
	  //cout<<(laserScan->ranges[i]<0.75); //primitive visualization of lazerz

	  if (inDeBox(i, laserScan->ranges[i])						//is this ping within range, 
		  && diff(laserScan->ranges[i],laserScan->ranges[i-1])	//and not much shorter than 
		  && diff(laserScan->ranges[i],laserScan->ranges[i+1])) //its neighboring points?
	  {
		  if (!jagFlag)
			  jagFlag = true;

		  if (objectInRange == false)
		  {
			  firstObstacleTheta = i;
		  }
		  objectInRange = true;
		  lastObstacleTheta = i; //will be overwritten until the last ping indebox
	  }
	  /*
	  if (laserScan->ranges[i]<0.75)
	  {
		  objectInRange = true;
	  }
	  */
	}
	nearestObstacle = shortestRange*sin((((180-nearestTheta)*PI)/180.0)); 
	//This is the braking distance for an obstacle in front of our track. 
	//for large boxes and obstacles just barely in the box, but whose theta
	//is large or small (0-10,170-180), stopping distance may be quite short.  
	holla = true;
	//cout<<endl;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "laser_listener");

	ros::NodeHandle n;

	ros::Rate r(HZ);
	
	ros::Subscriber sub = n.subscribe(LISTENTOTHIS,1,laserCallback);

	ros::Publisher pub = n.advertise<beta_nodes::obstacle>("obstacle", 10);
	
	beta_nodes::obstacle obstacleMsg;

	//ros::spin();
	while(!ros::Time::isValid())
	{
		ros::spinOnce();
	}

	while(ros::ok())
	{
		objectInRange = false;
		ros::spinOnce(); //triggers callbacks 
		if (holla)//only execute below if callback occured
		{
			holla = false;

			obstacleMsg.nearestObstacle = nearestObstacle;
			obstacleMsg.nearestTheta = nearestTheta;

			if (objectInRange)
			{
				obstacleMsg.obstacle = true;
			}
			else
			{
				obstacleMsg.obstacle = false;
			}
		
			obstacleMsg.leftClearance = leftClearance;
			obstacleMsg.rightClearance = rightClearance;
			
			obstacleMsg.edgeDistance = edgeDistance;
			obstacleMsg.edgeTheta = edgeTheta;
			
			obstacleMsg.firstObstacleTheta = firstObstacleTheta;
			obstacleMsg.lastObstacleTheta = lastObstacleTheta;
			
			pub.publish(obstacleMsg);
		}
		else 
		{
		//	  cout << "RATE IS MORE THAN FAST ENOUGH" << endl;
		}

		r.sleep();

	}
	return 0;
}
