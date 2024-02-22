
Software requirement:
1.	Ubuntu 20.4
2.	ROS Noetic
3.	Python3
4.	Ardono IDE 1.8.15
5.	Tkinter GUI python library

Source material:
1.	Ubuntu 20.04 installation: https://www.youtube.com/watch?v=BnV23ZEI34w
2.	Arduino installation tutorial: https://www.youtube.com/watch?v=QTK1g0P8OUM&list=PLVZDfM16Af8nOa5SLcIAcPFzIGaJhaRgs&index=7&t=5875s

Hardware requirement:
1.	Arduino UNO R3 1
2.	LED POWER SUPPLY RC-A60VA
3.	MG 90S servo 1
4.	SG 90 servo 1
5.	E6B2-CWZ6C Encoder Omron 2

Step to install:
1. Go to the GitHub page of the code you want:
2. Click the "Clone or download" button:
3. Select "Clone with HTTPS":
4. Copy the HTTPS URL https://github.com/Meen-Shuxin/PR_Robot_Arm.git:
5. Open a terminal on your computer:
6. Go to the folder where You want to keep the code:
7. Run the git clone command with the URL you copied:
     Git clone https://github.com/Meen-Shuxin/PR_Robot_Arm.git
8. Go to the folder where you cloned the code:
9. Run the “catkin build” or “catkin_make” command:
10. Go to the folder where you cloned the code:
11. Run the roslaunch <package_name> <node_name> port:="{Your port}" command:
		  roslaunch control control.launch port:="dev/ttyUSB0"
