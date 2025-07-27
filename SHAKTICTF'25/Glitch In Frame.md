<img width="738" height="220" alt="image" src="https://github.com/user-attachments/assets/1f70ba80-4e77-40cd-a375-38ac7aad9344" />  

Fun forensics chall for sure.  
Open pcap file with Wireshark.   

<img width="1669" height="490" alt="image" src="https://github.com/user-attachments/assets/0f686a59-f261-4ca3-9cfd-7d168d00ef13" />  

As you can see, packet no 10 has big size (6753) and contain GIF file in it.   

<img width="280" height="65" alt="image" src="https://github.com/user-attachments/assets/8d8c4619-a797-400b-a689-6847470128a4" />  

Export that specific packet to extract that GIF file.  
Follow TCP stream -> Save as -> flag.gif.  
We can't open it yet. Open HxD and edit that gif file. Below is GIF's file signature.    
```
Start: 47 49 46 38 39 61 = GIF89a    
End: 3B = ; (GIF terminator)    
```
After you successfully recover gif file you have the flag. If it's still hard to read ( bcuz it's gif), use any tool online to capture image by image.  
Peace!





