<img width="530" height="590" alt="image" src="https://github.com/user-attachments/assets/8f530565-f4da-4994-8071-b973c8774684" />  


# Cre : namdory

Mở file bằng IDA. Ở hàm main ta có thể thấy lời gọi hàm tới hàm vuln  

<img width="688" height="150" alt="image" src="https://github.com/user-attachments/assets/fb33f87c-5bec-4803-8128-3e87e848060f" />  

 
=>	Hàm chứa lổ hổng cần khai thác  
Ở trong hàm vuln ta thấy dùng gets() để đọc đầu vào từ người dùng vào vùng nhớ ebp-4   

<img width="686" height="72" alt="image" src="https://github.com/user-attachments/assets/28d5e01a-bbce-4d16-b279-3b3d1bdd9d22" />  

 
=>	Dễ bị khai thác Buffer Overflow  
Ở hàm win() có thể thấy chứa file flag ẩn   


<img width="940" height="189" alt="image" src="https://github.com/user-attachments/assets/6b617306-fd27-41b8-b808-3459f395f3dd" />  

 
=>	Tìm địa chỉ của hàm win()  
Trên Kali thử chạy  lệnh ` checksec vuln1  `

<img width="459" height="309" alt="image" src="https://github.com/user-attachments/assets/e2205cd8-1209-4d41-b2b9-95d2f109583d" />  

<img width="940" height="612" alt="image" src="https://github.com/user-attachments/assets/eda81485-f26d-4c97-9af5-7ee1def8319e" />  
 

=>	Đây là một chương trình lý tưởng để khai thác buffer overflow  
Tiếp theo sẽ đi tìm offset để ghi đè return address  
B1: Tạo payload cyclic(200)  
`python3 -c "from pwn import *; print(cyclic(200))" > input.txt  `  
B2: Sử dụng gdb  
```vim
gdb ./vuln1  
run < input.txt  
info registers
```

<img width="856" height="594" alt="image" src="https://github.com/user-attachments/assets/46d44b50-3668-4e6e-a65a-c538a4e8ec84" />  

 
=> Tìm được giá trị thanh ghi EIP là  0x616c6161  
B3: Tìm offset với cyclic_find  
`python3 -c "from pwn import *; print(cyclic_find(p32(0x616c6161)))" `  
Kết quả thu được là 42 -> offset là 42  
Nhưng phân tích lại hàm vuln()  

<img width="940" height="467" alt="image" src="https://github.com/user-attachments/assets/2b8429f7-402e-4e37-ab68-64fcfc55eb4d" />  

 
B4: Tìm địa chỉ hàm chứa flag  
Tiếp tục sử dụng GDB gõ `info functions`  

<img width="725" height="874" alt="image" src="https://github.com/user-attachments/assets/4813a64f-66e4-4854-b809-66f5944c1a5f" />  

=>	Hàm win là hàm chứa flag với địa chỉ là 0x08049276  
Cuối cùng sử dụng payload sau để tìm ra flag   
<img width="602" height="678" alt="image" src="https://github.com/user-attachments/assets/04fbf044-0649-4a24-aa4f-6a68f9ab619a" />  

 
 
> Flag: BDSEC{Woody_Stack_Smash_123}
