#include <OVR_CAPI_0_5_0.h>
#include <iostream>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

void Application()
{
  if (ovr_Initialize(NULL))
    {
      ovrHmd hmd = ovrHmd_Create(0);
      int hmdCount = ovrHmd_Detect();
      int i =0;
      static tf::TransformBroadcaster br;
      tf::Transform transform;
      transform.setOrigin(tf::Vector3(0.0,0.0,0.0));
      tf::Quaternion q;
      
      std::cout << "Hmd count is " << hmdCount << std::endl;
      if (hmd)
	{
	  // Get more details about the HMD.
	   ovrSizei resolution = hmd->Resolution;
	   std::cout << "Hmd resolution (width) is " << resolution.w << " pixels"<< std::endl;
	   std::cout << "Hmd resolution (height) is " << resolution.h <<" pixels"<< std::endl;
	   //Initialize tracking and sensor fusion
	   ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);
	   while (ros::ok())
	     {
	   //Query the HMD for the current tracking state
	   ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
	   if (ts.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked))
	     {
	       // std::cout << "It just read" << std::endl;
	       float x = ts.HeadPose.ThePose.Orientation.x;
	       float y = ts.HeadPose.ThePose.Orientation.y;
	       float z = ts.HeadPose.ThePose.Orientation.z;
	       float w = ts.HeadPose.ThePose.Orientation.w;
	       q.setValue(x,y,z,w);
	       // std::cout << "Sample "<< i << " = " << ts.HeadPose.ThePose.Orientation.x << std::endl;
	       transform.setRotation(q);
	       br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "oculus_rift"));
	     }
	     }
	   ovrHmd_Destroy(hmd);
	}
      ovr_Shutdown();
    }
}

int main(int argc, char **argv)
{
  std::cout << "The Driver has started" <<std::endl;
  ros::init(argc, argv, "orros_driver");
  ovr_Initialize(NULL);
  Application();
  return 0;
}
	  
