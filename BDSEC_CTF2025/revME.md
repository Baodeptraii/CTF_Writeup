<img width="545" height="549" alt="image" src="https://github.com/user-attachments/assets/1f20b881-8c1e-4607-a1d7-b8479e6b13ee" />  

Kiểm tra bằng một số command đơn giản :  

<img width="662" height="163" alt="image" src="https://github.com/user-attachments/assets/021b4252-d543-4762-bcf4-06546bc41531" />  

Phân tích bằng IDA:  

<img width="382" height="338" alt="image" src="https://github.com/user-attachments/assets/9600f669-0639-4a0f-a110-42eeb8254acd" />  

- Biến `v0` chỉ tới `enc_hint`
- Biến `v1` chỉ tới `_bss_start` ( vùng nhớ dành cho dữ liệu chưa được khởi tạo )
- Biến `v2` khởi tạo = `/x05`
- Vòng lặp:
  - `v1` được tính bằng cách XOR từng byte của `key` với biến `v0`, lưu kết quả vào `_bss_start`
  - `v2` giảm dần sau mỗi vòng lặp => Lặp 5 lần ~ 5 bytes  

Sau khi lặp xong, in ra giá trị được lưu ở `_bss_start` ~ `BDSEC`  

Phân tích tiếp trong IDA, ta thu tập được giá trị của các biến :  
```
enc_flag db 0E8h                        ; DATA XREF: LOAD:00000000004000C0↑o
enc_hint db 0E8h                        ; DATA XREF: _start↑o
     key db 0AAh                             ; DATA XREF: _start+15↑r
```

- Key thu được : `0xAA`
- `enc_flag` và `enc_hint` đều là `0xE8` ~ có thể là bắt đầu của một mảng giá trị.

Output thu được là `BDSEC` aka kết quả sau khi XOR với khóa, dịch ngược :  
```
"B" = 0x42 = enc_hint[0] ^ 0xAA  
→ enc_hint[0] = 0x42 ^ 0xAA = 0xE8  
"D" = 0x44 = enc_hint[1] ^ 0xAA  
→ enc_hint[1] = 0x44 ^ 0xAA = 0xEE  
"S" = 0x53 = enc_hint[2] ^ 0xAA  
→ enc_hint[2] = 0x53 ^ 0xAA = 0xF9  
"E" = 0x45 = enc_hint[3] ^ 0xAA  
→ enc_hint[3] = 0x45 ^ 0xAA = 0xEF  
"C" = 0x43 = enc_hint[4] ^ 0xAA  
→ enc_hint[4] = 0x43 ^ 0xAA = 0xE9
enc_hint thực tế có thể là :
enc_hint = [0xE8, 0xEE, 0xF9, 0xEF, 0xE9]
```

<img width="114" height="43" alt="image" src="https://github.com/user-attachments/assets/d3adc121-073c-4ec3-8d9f-2b72449ce8b8" />  

Độ dài flag cần tìm là 20, hint là 5 ( done ).   

<img width="529" height="408" alt="image" src="https://github.com/user-attachments/assets/7de7efef-339c-43d3-a4fd-048fd565e69a" />  

`Enc_flag` tìm được trong IDA, có thể thấy 5 bytes đầu đã trùng khớp với `enc_hint`, ta chỉ cần XOR những byte còn lại với khóa `0xAA` là tìm được flag.  

```
key = 0xAA
enc_flag = [
    0xE8, 0xEE, 0xF9, 0xEF, 0xE9,
    0xD1, 0xD8, 0x99, 0xFC, 0xF5,
    0xC7, 0x99, 0xF5, 0xEB, 0xD9,
    0xE7, 0xF5, 0xE8, 0xEE, 0xD7
]

flag = bytes([b ^ key for b in enc_flag])
print(flag)
```
> flag: BDSEC{r3V_m3_AsM_BD}







