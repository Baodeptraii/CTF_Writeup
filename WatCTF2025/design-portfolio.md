<img width="491" height="425" alt="image" src="https://github.com/user-attachments/assets/e548cb4c-348e-455a-836c-116349c55aee" />  

Another take time chal with Wireshark.  
When i trying to look around every packets, i found something like :  

<img width="1190" height="94" alt="image" src="https://github.com/user-attachments/assets/380cd876-f3ba-4d57-a92a-cf016c65bb18" />  

or  

<img width="359" height="680" alt="image" src="https://github.com/user-attachments/assets/d5dd4626-b984-4c92-b712-1805986d9ffb" />  

all of them has no clue. Then i follow tcp stream to read the data.  

<img width="426" height="254" alt="image" src="https://github.com/user-attachments/assets/3c7ef219-4a6e-472e-b406-ec5d03154802" />  

X-Flag with 14 chucks ( part ), the first Chuck-001 start with `89504E47...` ??? Oh that PNG file signature. My idea is collect all the Chuck start with 001 to 014 and convert it to PNG format.  
Python script after i collected all.  
```python
concatenated_hex = ( "89504E470D0A1A0A.... <this one is all the HEX value concat into a string>"
)
data = bytes.fromhex(concatenated_hex)
with open("flag.png","wb") as f:
    f.write(data)
```
Open the pic:  

<img width="1033" height="267" alt="image" src="https://github.com/user-attachments/assets/e7c98fac-e8f3-4ff7-a16b-68ffa1c74de3" />  

> Actually, just throw the pcap file to chatgpt and it give you the full pic, i'm suprise with its power now ...

Peace!






