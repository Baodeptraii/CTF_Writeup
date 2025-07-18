Description:  
Here is a binary that has enough privilege to read the content of the flag file but will only let you know its hash. If only it could just give you the actual content!  

The same access like "hash-only-1".  
After SSH to the server, using `ls -lia` command, i dont see any `flaghasher` file.  
Using `find / -type f -name "flaghasher"` to locate where it is and i see:  
<img width="275" height="70" alt="image" src="https://github.com/user-attachments/assets/05414659-61c7-487a-b7ea-3bff40286bad" />  
Tried to `cd` to it location but didn't work. It shown:  
`-rbash: cd: restricted`  
That mean, the system restrict us to do some commands which include `cd`.  
It's called :  "Restricted Bash" (rbash) and our job now is trying to escape form it. Using `echo $0` to check. If the output is `-rbash` we still in the jail, if not, we're free.   
I use ` env /bin/sh` and it change my pwd to something strange but `echo $0` doesn't show `-rbash` anymore. That mean i can do some command with `flaghasher` file.  
Checking if i can run it normaly by `/usr/local/bin/./flaghasher` , and it work fine.  
Use the same technique in "hash-only-1" challenge and we have the flag.  
Peace!
