#include <math.h>
#include <ros/ros.h>
#include <cwru_base/Pose.h>
#include <sensor_msgs/LaserScan.h>
#include <beta_nodes/obstacle.h>
#include <iostream>
#include <beta_nodes/PathSegment.h>
#include <beta_nodes/steeringMsg.h>
#include "Path.h"
#include <vector>

#define CUTOFF 5 //disregard this many degrees of laser scan from the edges
#define HZ 10.0
#define PI 3.141562653589
#define D2R 0.0174532925 //pi/180
#define R2D 57.2957795
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
bool haveApproached=false;
bool postApproach=false;
Vector position,midPoint;
struct gap{
Vector right,left;
};
vector<gap> gaps;
Path path;

void steeringCallback(const beta_nodes::steeringMsg::ConstPtr& str){
	position.x = str->posX;
	position.y = str->posY;
	//ROS_INFO("Got Position");
}

void pathQueueCallback(const beta_nodes::PathSegment::ConstPtr& pth){
	if(pth->seg_type == 0){
		path.type = 0;
	}
	path.start.x = pth->init_point.x;
	path.start.y = pth->init_point.y;
	path.end.x = pth->ref_point.x;
	path.end.y = pth->ref_point.y;
	path.type = pth->seg_type;
	path.seg_psi = pth->seg_psi;
	path.t_hat.x = cos(path.seg_psi);
	path.t_hat.y = sin(path.seg_psi);
	path.n_hat.x = -(path.t_hat.y);
	path.n_hat.y = path.t_hat.x;
}

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
			//cout << "x";
			result = true;
		}
	}

	return result;
}



bool inThreatRange(int theta, float r)
{

	beta_nodes::obstacle referenceMsg; //this is used to get the constants from the message
	bool result = false;

	if(abs(r*sin(theta*D2R))<referenceMsg.threatRange) //abs() hack for negative values ...
	{
		//ROS_INFO("IN THREAT RANGE");
		result = true;
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
	float shortestRange = 999.999;
	bool eventType=false;
	int leftI=180, rightI=0;
	Vector leftPoint,rightPoint;
	gap tempGap;
	gaps.erase(gaps.begin(),gaps.begin()+gaps.size());
	//cout << "-=-=-=-=-=-=-= C A L L B A C K =-=-=-=-=-=-=-=-=-";

	rightClearance = laserScan->ranges[CUTOFF];
	leftClearance = laserScan->ranges[180-CUTOFF];

	for(uint i = CUTOFF; i < 180-CUTOFF; i++)
	{
	  //cout << inDeBox(i, laserScan->ranges[i]);
	  //cout<<(laserScan->ranges[i]<0.75); //primitive visualization of lazerz

		if (inDeBox(i, laserScan->ranges[i])						//is this ping within range, 
			&& diff(laserScan->ranges[i],laserScan->ranges[i-1])	//and not much shorter than 
			&& diff(laserScan->ranges[i],laserScan->ranges[i+1])) //its neighboring points
		{
		//postApproach=true;

		if (objectInRange == false)
		{
			firstObstacleTheta = i;
		}
		objectInRange = true;
		lastObstacleTheta = i; //will be overwritten until the last ping indebox
		if (laserScan->ranges[i]<shortestRange)
		{
			shortestRange = laserScan->ranges[i];
			nearestTheta = i;
		}
	  }
	  
		if(!inThreatRange(i,laserScan->ranges[i])
	  		&& diff(laserScan->ranges[i],laserScan->ranges[i-1])
			&& diff(laserScan->ranges[i],laserScan->ranges[i+1]))
		{
	  	if(eventType==false){
	  		eventType = true;
	  		//Store initial point
	  		rightI=i;
	  		rightPoint.x = laserScan->ranges[i]*cos(i*D2R);
	  		rightPoint.y = laserScan->ranges[i]*sin(i*D2R);
	  	}
	}
		else if(inThreatRange(i,laserScan->ranges[i])
			&& diff(laserScan->ranges[i],laserScan->ranges[i-1])
			&& diff(laserScan->ranges[i],laserScan->ranges[i+1]))
		{
	  	if(eventType){
	  		eventType=false;
	  		//Store end point, store event
	  		//If not wide enough don't store
	  		leftI = i;
	  		leftPoint.x = laserScan->ranges[i]*cos(i*D2R);
	  		leftPoint.y = laserScan->ranges[i]*sin(i*D2R);
	  		if(abs(leftPoint.x - rightPoint.x)> 0.6){
	  			//Store it
	  			midPoint.x = (leftPoint.x-rightPoint.x)/2;
	  			midPoint.y = (leftPoint.y-rightPoint.y)/2;
	  			tempGap.right = rightPoint;
	  			tempGap.left = leftPoint;
	  			ROS_INFO("%f - %f = %f",leftPoint.x, rightPoint.x, leftPoint.x - rightPoint.x);
	  			gaps.push_back(tempGap);
			}
		}
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
	//holla signifies we got info back from the laser
	holla = true;
	//cout<<endl;
	//ROS_INFO("Right: %f %f",rightPoint.x, rightPoint.y);
	//ROS_INFO("Left: %f %f",leftPoint.x,leftPoint.y);
}

void holdingPattern(double time){
	double t=0;
	double dt = 1.0/HZ;
	ros::Rate naptime(HZ);
	while(ros::ok() && t<time){
		ros::spinOnce();
		t=t+dt;	
		naptime.sleep();
	}
	return;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "replan");

	ros::NodeHandle n;

	ros::Rate r(HZ);
	
	ros::Subscriber sub = n.subscribe(LISTENTOTHIS,1,laserCallback);
	
	ros::Subscriber sub1 = n.subscribe("cmd_corr",1,steeringCallback);
	
	ros::Subscriber sub2 = n.subscribe("paths",1,pathQueueCallback);

	ros::Publisher pub = n.advertise<beta_nodes::obstacle>("nunya_obstacle", 1);
	
	ros::Publisher pub1 = n.advertise<beta_nodes::PathSegment>("replanning",1);
	
	beta_nodes::obstacle obstacleMsg;
	beta_nodes::PathSegment pathSegment;
	double distToGo;
	Vector avoidPoint;
	avoidPoint.x=999;
	avoidPoint.y=999;
	//ros::spin();
	while(!ros::Time::isValid())
	{
		ros::spinOnce();
	}
	
	holdingPattern(1);

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
				//ROS_INFO("%f %d",nearestObstacle, nearestTheta);
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
			double graft = 999.0;
			int theOneToUse=0;
			bool edge=false; //edge false, right point closest, go left
					 //edge true, left point closest, go right
			for(int i=0;i<gaps.size();i++){
				if(abs(gaps[i].right.x)<graft){
					graft = gaps[i].right.x;
					theOneToUse = i;
					edge=false;
				}
				if(abs(gaps[i].left.x)<graft){
					graft = gaps[i].left.x;
					theOneToUse = i;
					edge=true;
				}
			}
			
			//Check to see if nearestObstacle is farther away than the current desired end point
			//If so, ignore, if not publish new seg to end at .55m away, or if it's closer, 30% away, or stop.
			distToGo = sqrt(pow(path.end.x-position.x,2)+pow(path.end.y-position.y,2));
			//ROS_INFO("%f",distToGo);
			if(obstacleMsg.obstacle && distToGo > nearestObstacle-0.65 && !haveApproached){
				//Publish new path to close ish
				//Will need to check for when an object pops in < 0.55m away
				pathSegment.init_point.x = position.x;
				pathSegment.init_point.y = position.y;
				pathSegment.ref_point.x = position.x + (nearestObstacle-0.65)*cos(path.seg_psi);
				pathSegment.ref_point.y = position.y + (nearestObstacle-0.65)*sin(path.seg_psi);
				avoidPoint.x = pathSegment.ref_point.x;
				avoidPoint.y = pathSegment.ref_point.y;
				pathSegment.seg_psi = path.seg_psi;
				pathSegment.seg_type = 1;
				pub1.publish(pathSegment);
				haveApproached=true;
				ROS_INFO("Pubed Path %f %f %f %d", pathSegment.ref_point.x,pathSegment.ref_point.y, nearestObstacle-0.55, pathSegment.seg_type);
			}
			distToGo = sqrt(pow(avoidPoint.x-position.x,2)+pow(avoidPoint.y-position.y,2));
			//ROS_INFO("ToGo: %f", distToGo);
			int dir;
			double n_psi = atan2(path.n_hat.y,path.n_hat.x);
			if(edge){ graft-=0.25;}
			else {graft+=0.25;}
			if(distToGo < 0.1 && haveApproached && !postApproach){
				postApproach=true;
				ROS_INFO("Graft: %f %d 0 go left, 1 go right",graft,edge);
				for(int i=0;i<gaps.size();i++){
					ROS_INFO("%f %f",abs(gaps[i].right.x),abs(gaps[i].left.x));
				}
				pathSegment.init_point.x = position.x + 0.65*cos(path.seg_psi) + graft*path.n_hat.x;
				pathSegment.init_point.y = position.y + 0.65*sin(path.seg_psi) + graft*path.n_hat.y;
				ROS_INFO("%f + %f + %f",position.x, 0.65*cos(path.seg_psi), graft*path.n_hat.x);
				ROS_INFO("%f + %f + %f",position.y, 0.65*sin(path.seg_psi), graft*path.n_hat.y);
				pathSegment.ref_point.x = pathSegment.init_point.x;
				pathSegment.ref_point.y = pathSegment.init_point.y;
				avoidPoint.x = pathSegment.ref_point.x;
				avoidPoint.y = pathSegment.ref_point.y;
				pathSegment.seg_type = 4;
				pub1.publish(pathSegment);
				ROS_INFO("Pubed Correction Seg %f %f %d", pathSegment.init_point.x,pathSegment.init_point.y, pathSegment.seg_type);
			}

		}
		else 
		{
		//	  cout << "RATE IS MORE THAN FAST ENOUGH" << endl;
		}
		r.sleep();

	}
	return 0;
}
