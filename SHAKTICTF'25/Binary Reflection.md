<img width="516" height="128" alt="image" src="https://github.com/user-attachments/assets/63e982dc-585c-47d3-b898-1781360ac6db" />  

Checking PDF file, we cant open it normally.  
Using HxD to check file signature:   

<img width="627" height="240" alt="image" src="https://github.com/user-attachments/assets/0243bcee-4256-4ce7-960e-56a1e8890c06" />  

<img width="645" height="166" alt="image" src="https://github.com/user-attachments/assets/906601a2-aa33-4e0d-84ce-4f153dacc71c" />  

Okay, it's reversed by **line**. Write a simple script to make it back to the normal.  
```python
with open("corrupt.pdf", "rb") as f:
    lines = f.readlines()
reversed_lines = lines[::-1]
with open("restored.pdf", "wb") as f:
    f.writelines(reversed_lines)

```
or you can use `tac` ( linux )  
```bash
tac corrupt.pdf > restored.pdf
```
But you need to check carefully again. PDF file start with `25 50 44 46` ~ `%PDF` and end with `25 25 45 4F 46` ~ `%%EOF`. Remember to double check it.  
Once you restore the PDF file and open it, you can see the flag.  
Peace!





