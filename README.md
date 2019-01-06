# Mobile Robots - Team 2
Project for Mobile_Robots. This repository contains robot source code for course Mobile Robots at NCTU 2018. This code got third place in final competition.

## Problem Reports
If you need any help please create a new issue here on github.

## Repository Structure
Branch *robot_master* contains commits for Robot Contest. This branch contains tags for each checkpoint. All checkpoint can be achieved by running the last code version (*robot_contest* tag).

Branch *hand_controll* contains code for Cool Robot Show.

Branch *master* contains this readme file.

## Log In to Raspberry PI 3
Raspberry PI is running Ubuntu MATE. Computer name and login name are *rpi3-2* the password is *rpi*. RPI is configured to automatically connect to wifi named *rpi3-2* with password *tatranky111*. Because the wifi was provide by Windows 10 hotspot, RPI could not use static IP and must requests DHCP server. Network adress was default *192.168.137.0/24*.

## Compiling the Source
On RPI3 you need to run this command:
```bash
cd catkin_ws/; catkin_make
```
 
If there is some compiling problem with missing dependencies you can first try to recompile CMakeLists.txt by:
```bash
cd catkin_ws/;
touch src/mobile-robots/motor_manager/CMakeLists.txt
catkin_make
```

## Running the Program
At first you need to start:
```bash
roscore &
cd catkin_ws/ ; source devel/setup.bash
rosrun rosserial_python serial_node.py /dev/ttyACM0 &
```

From fourth checkpoint (where the robot needs to find gate) program require the parameters. You need to run next command where *<INFRA_RED_FREQ>* is value *600* or *1500* depends on which gate needs to find:
```bash
rosrun robot_core robot_run <INFRA_RED_FREQ>
```
 
For final contest we added more parameters but you can still run program with only one parametr as in fourt checkpoint
```bash
- rosrun robot_core robot_run <INFRA_RED_FREQ>
```
or
```bash
- rosrun robot_core robot_run <INFRA_RED_FREQ> <LEFT_SPEED> <RIGHT_SPEED> <FORWARD_TIME>
```
where <LEFT_SPEED> <RIGHT_SPEED> <FORWARD_TIME> are params for initializing *direct_search* program which tries to reach the puck directly and if it isn't successful then it switchs to *random_search* program.

Next table shows usable values for params. Letters is robot starting position and number is puck starting position.

| |left | right | time | 
|:----|:----:|:-----:|:------:|
| a1 | 154 | 235 | 2050 | 
| a2 | 167 | 235 | 1750 | 
| a3 | 235 | 214 | 1800 | 
| b1 | 187 | 230 | 1550 | 
| b2 | 235 | 214 | 1200 | 
| b3 | 235 | 214 | 1350 | 
| c1 | 221 | 235 | 1750 | 
| c2 | 235 | 214 | 1400 | 
| c3 | 235 | 214 | 1200 | 

Robot can be stoped by hitting the *ctrl+c*.

## FAQ
### Unable to use apt-get on RPI3
```
E: Could not get lock /var/lib/dpkg/lock - open (11: Resource temporarily unavailable)
E: Unable to lock the administration directory (/var/lib/dpkg/), is another process using it?`
```

It is possible that auto update is running. You can check it by *ps -e | grep  unattended-upgr*. If you find any process with that name running then that it is. You must to wait for end of that process. You can also check udpates log */var/log/dpkg.log*, or the files in */var/log/unattended-upgrades/*.

### Usage of application: screen
* For starting new screen session type *screen*
* For detaching screen use key combination ctrl+a+d
* For attaching dettached screen use command *screen -r*

### How to enable remote GUI application
1. Download [vcxsrv](https://sourceforge.net/projects/vcxsrv/)
2. To allow connection to your XServer, you must add IP address of RPI to file X0.hosts in directory where vcxsrv is installed.

   If you want to allow everyone to connect your XServer, then instead of IP type *xhost*.
```
localhost
inet6:localhost
192.168.137.168
```
3. Start XLaunch, set display number to 0.

   If there is not running XServer then -1 will be substitued as 0 automatically.
4. ~~Type in RPI terminal (via SSH) *export DISPLAY=<YOUR_IP>:0.0* with <YOUR_IP> substitued for your IP address.~~ *Automatized for user rpi3-2 in .bashrc*
5. Try to start application *xeyes* via SSH to see if everything is working.
