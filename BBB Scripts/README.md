# BBB Scripts
This folder contains scripts to automate some of the setup processes on the BBB.
eg: Enabling CAN1 interface.

# Basics of making script file
Note: Scripts created in Windows maybe throw errors in Linux because of different End-Of-Line for Unix systems.
1. Open a terminal and run following to create a script file:
    `sudo nano scriptname.sh`
2. Start with `#!/bin/bash`. Then add required shell commands in the next lines. 
2. Change permission to enable execution. From a terminal:
    `sudo chmod a+x scriptname.sh`
3. Run script from terminal using: 
    `./scriptname.sh` or `sh scriptname.sh` or `bash scriptname.sh`

# Script additional
1. `#` is used for comments
2. `echo` to display on screen
3. `read var1` to read user input and store in var1. `$var1` is used to access variable value.
4. `&` at end of command runs it in background. Equivalent to ctrl+z followed by `bg`.
5. `sleep 5s` is used to wait for 5s. Can use m for mins, h for hours and d for days.