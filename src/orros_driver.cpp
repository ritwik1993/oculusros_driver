#include <OVR_CAPI_0_5_0.h>
#include <iostream>

void Application()
{
  if (ovr_Initialize(NULL))
    {
      ovrHmd hmd = ovrHmd_Create(0);
      int hmdCount = ovrHmd_Detect();
      std::cout << "Hmd count is " << hmdCount << std::endl;
      if (hmd)
	{
	  // Get more details about the HMD.
	   ovrSizei resolution = hmd->Resolution;
	   std::cout << "Hmd resolution (width) is " << resolution.w << " pixels"<< std::endl;
	   std::cout << "Hmd resolution (height) is " << resolution.h <<" pixels"<< std::endl;
	   ovrHmd_Destroy(hmd);
	}
      ovr_Shutdown();
    }
}

int main()
{
  std::cout << "The Driver has started" <<std::endl;
  ovr_Initialize(NULL);
  Application();
  return 0;
}
	  
