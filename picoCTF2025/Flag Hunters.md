Description:  
Lyrics jump from verses to the refrain kind of like a subroutine call. There's a hidden refrain this program doesn't print by default. Can you get it to print it? There might be something in it for you.  
Hints:  
This program can easily get into undefined states. Don't be shy about Ctrl-C.  
Unsanitized user input is always good, right?  
Is there any syntax that is ripe for subversion?  

After download and read the source code, i found out that the input in `crowd = input('Crowd: ')` is unsanitized which mean it will print anything you type into it.  
I tried to injected a python payload to read flag.txt directly but not working so that i decide to read the code carefully.  
Our mission is make the program jump to this part:  
<img width="563" height="258" alt="image" src="https://github.com/user-attachments/assets/17cb69db-2803-4226-8fe9-b84516f986dc" />  
This code will trigger it i guess:  
<img width="430" height="104" alt="image" src="https://github.com/user-attachments/assets/32ffbef9-0ab7-44b5-9b65-8e39c18e1783" />  
I input this  `;REFRAIN;RETURN 3;`  to control the program and i got the flag.  

Peace!

 

