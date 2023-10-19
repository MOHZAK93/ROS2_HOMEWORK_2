___________________________________________
                Requirements                              
===========================================

Create two packages one that is using python3 and the other using C++.

 

Python3 package:
================

==> Name the package after your favorite fruit. and the executable should be called webcam_driver

==> This package should leverage OpenCV to read in your webcam draw the current time in seconds on the image then publish the image topic called /webcam/image_raw. Publish the image using the Best_Effort  QoS.

C++ package:
============

==> Name the package after your favorite color. And call the executable color_filter

==> This package should read in the image topic you published and modify the colors see this link

==> For the code below use parameters to change the numbers of the filter so that you can modify which color you are trying to detect and change the color to red. (0,0,255)

---------------------------------------------------------------------------
brown_lo=np.array([10,0,0])
brown_hi=np.array([20,255,255])


#psudo code
param_lo = [10,50,255]
param_hi = [255,255,10]

------------------------------------------------------------------------------------------------

Create a launch file in the C++ package that will call the python3 web_cam node and the C++ node with the parameters you specify.

Result:
======

Your final result should be your webcam image that has the current time in seconds rendered on the image and you can choose which colors to detect in the image (try to detect blue) and change the blue pixels to red.

 

Use git, you must send me the link to your github repository where you stored the code, You can use a private repo and send me an invite to see the project
 


