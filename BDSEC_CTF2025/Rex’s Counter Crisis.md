<img width="516" height="596" alt="image" src="https://github.com/user-attachments/assets/6f292859-85e3-44e6-a4e0-7e90487adbc5" />  

Kiểm tra bằng OS command:  

<img width="670" height="118" alt="image" src="https://github.com/user-attachments/assets/71835373-d3d3-4ab8-a969-b2c76a26ba8c" />  

Lựa chọn IDA32 để phân tích :  

<img width="517" height="157" alt="image" src="https://github.com/user-attachments/assets/76523723-567e-468a-8c89-8731378ffc55" />  

Cảnh báo ở trên có thể không quan tâm, biến `v8` được khai báo với 25 phần tử ~ 100 bytes ở trên stack.  
Các biến còn lại chỉ là padding phụ, bỏ qua.  

<img width="210" height="463" alt="image" src="https://github.com/user-attachments/assets/0890109c-323f-4be7-8a5c-7f9983874629" />  

`setbuf` chỉ nhận 2 tham số: `setbuf(FILE *stream, char *buf)`  
Chứng tỏ stack bị lệch → có thể là vết tích của buffer overflow.  

<img width="365" height="194" alt="image" src="https://github.com/user-attachments/assets/922f1286-908d-410a-9701-986498b17000" />  

Yêu cầu nhập input, `%hu` đọc một số nguyên ~ 2 bytes và lưu vào `(char *)&v9 + 2`.  
`if ( HIWORD(v9) > 0x64u )` => Nếu input > 100 ( x64) thoát chương trình.  

`__isoc99_scanf("%s", (char *)v8 + 2);` yêu cầu nhập thêm chuỗi nữa để lưu vào `v8` nhưng lại ghi vào ` (char *)v8 + 2` ( lệnh 2 bytes )  

Có một lời kiểm tra đặc biệt :   
```
if ( HIWORD(v9) == 0xFFFF )
    win(p_argc);
```
Nếu có kí tự `0xFFFF` ( 65535 ) thì sẽ gọi được hàm `win()` - thường là nơi chứa kết quả. Nhưng bên input > 100 thì bị thoát rồi mà ?  

Nhìn vào biến `v8`, nó đang để chừa 2 bytes cuối cùng. Vậy giả sử, ta nhập đủ tối đa số byte `v8` có thể chứa ( 100 ) và buffer thêm 2 bytes nữa `( 0xFFFF )`, liệu nó có nhảy sang `v9` không ?  

Ý tưởng là `v9` ta nhập tối đa 100 bytes để lưu, `v8` đưa đủ 100 bytes padding và thêm 2 bytes `0xFFFF` nữa để gây Buffer Overflow.  

```
import sys
from pwn import *

payload = b"A" * 100 + b"\xFF\xFF"
sys.stdout.buffer.write(b"100\n")
sys.stdout.buffer.write(payload + b"\n")
```

> flag: BDSEC{Rex_Int_Overflow_012}

Peace!







