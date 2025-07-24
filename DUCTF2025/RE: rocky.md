<img width="1026" height="661" alt="image" src="https://github.com/user-attachments/assets/34b0bdc7-7b44-4c27-9911-7850452c2c79" />  


Using IDA to decomplied the code and we have:  

<img width="521" height="395" alt="image" src="https://github.com/user-attachments/assets/28a29a34-54a5-4998-af81-97a2b7560eb2" />  

Given `s1[0]` and `s1[1]` which are 8 bytes.  
Enter input and store at `s`.  
Calc md5 string of `s` and store at `s2`.  
Then compare `s1` with `s2`.  
Two arguments of `s1` was given above. Write a simple script to calc it.  
```python
s1 = (-3244445551054450064).to_bytes(8, byteorder='little', signed=True)
s2 = (2248705866729376316).to_bytes(8, byteorder='little', signed=True)
target_md5 = s1 + s2
print(target_md5.hex())
```
We receive:  
>  70924d0cf669f9d23ccabd561202351f

Use exited tool to calc the text instead of using dictionary.  

<img width="1275" height="460" alt="image" src="https://github.com/user-attachments/assets/2709138d-3d1d-469a-842d-a7f291997ada" />  

Execute the file with that input and we got the flag!  

Peace!




