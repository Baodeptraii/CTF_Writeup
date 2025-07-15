Description:  
Welcome to the challenge! In this challenge, you will explore a web application and find an endpoint that exposes a file containing a hidden flag.
The application is a simple blog website where you can read articles about various topics, including an article about API Documentation. Your goal is to explore the application and find the endpoint that generates files holding the server’s memory, where a secret flag is hidden.  
Hints:  
Explore backend development with us  
The head was dumped.  

Launch instance and go to given website. It's absolutetly normal to look up. Use `Ctrl + U` to view the source code and find any link.  
Only this link directs us to another page:  
<img width="1127" height="112" alt="image" src="https://github.com/user-attachments/assets/20488809-b672-4324-8263-5596ee4be0cf" />  
Read the hint, they said "the head" so i guess something was hidden in headdump. Using that page to extract headdump.  
<img width="771" height="290" alt="image" src="https://github.com/user-attachments/assets/27c480c2-aa35-43de-90a2-70c7957983a1" />  
Download this headsnapshot, extract and read the file to find the flag:  
`strings <your_file> | grep "CTF"`

Peace!



