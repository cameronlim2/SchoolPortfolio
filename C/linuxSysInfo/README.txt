Created for CSC 139 at CSUS

System information for Linux Systems. Returns the following information:
CPU Model
Version of Linux
Time since last system reboot
CPU time spent [User/System/Idle]
Total Memory
Available Memory
Disk Read/Write Requests
# of Context Switches
Total # of Processes


-----------------------------------------------------------------------------------------

To Run:

go to directory with partd.c
	gcc partd.c -o partD
	partD | partD [-s] | partD -s [-l int dur] 

-----------------------------------------------------------------------------------------

Only known error: Total process count comes out as Segmentation Error.
