# mobile_robots
Project for Mobile_Robots

## Repository structure
Each one catkin package is in its own package-master branch. For each package-master branche exists developing branch with suffix *\_dev*.

## HW and its Configuration
This chapter describes used hardware for project and its configuration.

### Raspberry PI 3
Raspberry PI is running Ubuntu MATE. Computer name and login name are *rpi3-2* the password is *rpi*. RPI is configured to automatically connect to wifi named *rpi3-2* with password *tatranky111*. Because the wifi is provided by Windows 10 hotspot, RPI can't use static IP and must requests DHCP server. Network adress is *192.168.137.0/24*.

[Backup of RPI3 from 29/09/2018](https://1drv.ms/f/s!AvqSf0K9YS3I8R9ceqbFbVfGaDds "One Drive") with updated OS and installed necessary stuffs.

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
