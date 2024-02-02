Paths in files might be different!

After compilation autorun_sn.exe need to be started by hand or reboot your device.
To stop autorun_sn (terminate the running background task and remove autorun_sn.exe from autostart), simply start terminate_autorun_sn.exe.

In ```source/autorun/autorun_sn.cpp```, ```source/main/main.cpp``` and ```source/terminate_autorun/terminate_autorun_sn.cpp```, there is one line of script needed to compile each part. All three of these scripts need to be executed in the directories they originated from.

I don't want to deal with an installer and files containing paths, so if you want to use this "running in the background and executing a script every 2 hours that does everything needed to write a text in the commit," then just go through the cpp and hpp files and change the paths to fit your device.