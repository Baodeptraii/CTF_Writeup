<img width="580" height="676" alt="image" src="https://github.com/user-attachments/assets/b8816081-080a-4f35-a895-886b1a3aa00f" />  

Giving us JSON file, like a blockchain or st.  
Some of blocks are diffirent from others: 101, 108, 117.  
Each block contains `op_return`.  
Read the description again and the name of investigator is 'B'.  
I come up with XOR every num in that `op_return` with character `B` ( 66 ) and it worked.  
```python
op_data = [
   0, 6,17,7,1,57,0,14,114,1,
   9,29,1,10,3,11,44,29, 6,55,
   47,18,29,115,119,29,4,55,44,44,27,63
]
res = ""
for b in op_data:
    res += chr(b ^ 66)
print(res)
```

Peace!


