Description:  
Here is a binary that has enough privilege to read the content of the flag file but will only let you know its hash. If only it could just give you the actual content!  

After follow the description i successfully access to server. Use `ls` command to check if there is `flaghasher` file.  
Tried to run it with `./flaghasher` and it's return to the md5 hash of `./root/flag.txt`.  
I use some hash decoder tools but it not working.  
Then i download the binary file, using IDA to open and read the code.  
<img width="569" height="112" alt="image" src="https://github.com/user-attachments/assets/8e36d110-714d-49be-a167-66d29cf2f5f6" />  
As you can see, there is a `system()` call, and the command is `"/bin/bash -c 'md5sum /root/flag.txt'"`.  
So everytime you run the binary file, i will run this command and print out `md5sum` of the path.  
So ... what if : we can create a fake `md5sum` file and trick and system to execute it instead of the real one ?  
There is my script :  
```
$ echo -e '#!/bin/bash\ncat "$@"' > md5sum
$ chmod +x md5sum
$ PATH=:$PATH ./flaghasher
```
So instead of calculate the md5sum of /root/flag.txt, the system will `cat` it instead.  
Peace!

