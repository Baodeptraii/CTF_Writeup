Description:  
One of the employees at your company has their computer infected by malware! Turns out every time they try to switch on the computer, it shuts down right after they log in. The story given by the employee is as follows:  
They installed software using an installer they downloaded online  
They ran the installed software but it seemed to do nothing  
Now every time they bootup and login to their computer, a black command prompt screen quickly opens and closes and their computer shuts down instantly.  
See if you can find evidence for the each of these events and retrieve the flag (split into 3 pieces) from the correct logs!  
Hints:  
Try to filter the logs with the right event ID  
What could the software have done when it was ran that causes the shutdowns every time the system starts up?  

Really fun challenge !  
We need to read the description to solve this chall.  
First one:  
`They installed software using an installer they downloaded online `  
=> We should find EventID about install which is Event ID 11707, Event ID 1033, MsiInstaller...  Use Filter in Event Viewer to apply that ID.  
We got the first piece of cake:  
`Information	15/07/2024 10:55:57 PM	MsiInstaller	1033	None`  

Next is:             
`They ran the installed software but it seemed to do nothing `  
=> So that mean, we should find the EventID about running a application, a process, ... But that didn't work for me. Having the first data, i see the application which was installed : `Totally_Legit_Software` ( lol )  
Find this name in EV, and i see the second one:  
`Information	15/07/2024 10:56:19 PM	Microsoft Windows security auditing.	4657	Registry`  

Last one:  
`they bootup and login to their computer, a black command prompt screen quickly opens and closes and their computer shuts down instantly`    
=> Which mean i need to find the EventID about : shutdown, bootup, login ... And it's working now with ID `1074` aka Indicates that an application (ex: a Windows update) or a user initiated a restart or shutdown.  
`Information	16/07/2024 12:01:05 AM	User32	1074	None`  
All the peices of cake is Base64, decode it and you get the flag.  

Peace!






