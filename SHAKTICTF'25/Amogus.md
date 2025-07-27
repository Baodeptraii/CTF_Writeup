<img width="714" height="136" alt="image" src="https://github.com/user-attachments/assets/b5577af1-34d3-4c7a-ac86-5a82a1686a2a" />  

Kiểm tra file bằng một số lệnh cơ bản:  

<img width="896" height="775" alt="image" src="https://github.com/user-attachments/assets/50c40134-1179-48ec-82ed-ffd826f57e75" />  

Dùng IDA để phân tích:  

<img width="508" height="201" alt="image" src="https://github.com/user-attachments/assets/edc2d967-8999-4d7b-a609-ba57de1d8509" />  

Nhập tên và lưu vào `v4`  

<img width="728" height="570" alt="image" src="https://github.com/user-attachments/assets/a0a4d12f-ea2d-4dd0-bc81-884d8b2bb892" />  

`v4` được gán sẵn là `DEAD`  
`v4` phải là `ALIVE` mới được đi tiếp.  
`scanf("%s", v4)` nhận giá trị của `v4` nhưng không giới hạn đầu vào.  
`v4` có kích thước được khai báo là 16 bytes. Chỉ cần đầu vào > 16 bytes là gây tràn bộ nhớ.  
```python
import sys

payload = b"A" * 16 + b"ALIVE" + b"\n"

sys.stdout.buffer.write(payload)

```

Peace!







