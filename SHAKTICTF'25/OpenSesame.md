<img width="667" height="192" alt="image" src="https://github.com/user-attachments/assets/81f08072-34d1-4b60-9048-25d99105cce4" />  

Kiểm tra cơ bản:  

<img width="888" height="289" alt="image" src="https://github.com/user-attachments/assets/b24e4de3-fee2-4bf4-ae04-b7d795a0a3b5" />  

Kiểm tra bằng IDA:  

<img width="528" height="670" alt="image" src="https://github.com/user-attachments/assets/1d146ae2-305f-42e2-9206-abc1b575dc86" />  

Cho một đống biến của mảng `v17` dài ngoằng và một hàm xử lý theo các seed.  
Đây là một đoạn mã C thực hiện kiểm tra đầu vào (input) từ người dùng, mã hóa nó bằng một chuỗi các phép biến đổi (bao gồm XOR với rand(), xoay bit trái và phải), sau đó so sánh với mảng cố định v17[] để xác định xem người dùng có nhập đúng "magic words" hay không.  
Người dùng nhập chuỗi :  
```python
puts("Your answer: ");
__isoc99_scanf("%s", s);

```
Chuyển hết thành số nguyên:  (ASCII -> Decimal)
```python
for ( i = 0; i < strlen(s); ++i )
  v16[i] = s[i];
```
XOR từng tí tự với hàm ngẫu nhiên `rand()`:  
```python
seed_one(); 
for (...) v16[i] ^= rand();
seed_two(); 
for (...) v16[i] ^= rand();
seed_one();
for (...) v16[i] ^= rand();
seed_two();
for (...) v16[i] ^= rand();
```
Tuy nhiên, kiểm tra kỹ thì các hàm XOR kia là :  <img width="178" height="70" alt="image" src="https://github.com/user-attachments/assets/acaec46b-fa04-479c-a269-f34c1d3e5311" />  
`srand()` luôn đặt lại seed sau mỗi lần XOR => có thể khôi phục được.  
Cuối cùng là xoay bit và nhân 3:  
```python
v16[i] = l_rotate(v16[i], 3);
v16[i] = 3 * r_rotate(v16[i], 35); // rotate right 3 bits (vì 35 mod 32 == 3)
```
Như vậy, ta cần làm ngược lại các bước: Chia 3 - tìm lại `rand()` - XOR ngược - in chuỗi.  

```python
import random

# Dữ liệu đầu ra (sau khi nhân 3)
v17 = [
    345, 312, 291, 321, 348, 315, 297, 348, 306, 369,
    216, 315, 315, 147, 315, 147, 315, 147, 315, 315,
    285, 282, 285, 282, 285, 285, 153, 150, 156, 153,
    150, 156, 150, 285, 153, 330, 318, 144, 363, 285,
    342, 153, 354, 285, 282, 285, 375
]

# Đảo ngược quá trình:
s = ''
for i in range(len(v17)):
    final_val = v17[i] // 3  # loại bỏ *3 cuối

    # Lấy lại các rand() tương ứng
    random.seed(1)
    r1 = [random.randint(0, 0x7fffffff) for _ in range(len(v17))]

    random.seed(2)
    r2 = [random.randint(0, 0x7fffffff) for _ in range(len(v17))]

    # đảo ngược XOR
    c = final_val ^ r1[i] ^ r2[i] ^ r1[i] ^ r2[i]
    s += chr(c)

print("Flag:", s)
```

Peace!






