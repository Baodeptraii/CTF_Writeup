<img width="790" height="306" alt="image" src="https://github.com/user-attachments/assets/b7af5ee1-3e0a-4be6-8c38-c86e5823ceee" />  

First time do this kind of chal, but not take too long to find the way.  

The flag is VNC password (8 byte hex) which is stored at `HKEY_CURRENT_USER\Software\TightVNC\Server` registry entry.  
We have the dump file `NTUSER.DAT`.  
I use some following commands:  
```bash
reged -e NTUSER.DAT
cd \Software\TightVNC\Server
ls
cat
```
<img width="689" height="391" alt="image" src="https://github.com/user-attachments/assets/caa33f90-3457-4da9-acfb-fb009dc184b1" />  

We have 8 hex bytes of pass. 

VNC pass always encrypted using hardcoded DES key: `23 52 6b 06 23 4e 58 07`.  

I used this command to decrypt it: 
```bash
echo -n 7e9b311248b7c8a8 | xxd -r -p | openssl enc -des-cbc --nopad --nosalt -K e84ad660c4721ae0 -iv 0000000000000000 -d -provider legacy -provider default | hexdump -Cv
```
> Flag:  ictf{Slay4U!!}

Peace!






