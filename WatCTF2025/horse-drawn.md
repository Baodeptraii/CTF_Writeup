<img width="499" height="429" alt="image" src="https://github.com/user-attachments/assets/3457bec6-d758-46a7-9b9d-27c304f15384" />  

Here is the main.py:
```python
#!/usr/bin/env python3
import sys
assert sys.stdout.isatty()
flag = open("/flag.txt").read().strip()
to_print = flag + '\r' + ('lmao no flag for you ' * 32)
print(to_print)
```

Normaly when you run it will print the flag but `to_print` variable has to plus with `'\r'`.  
In python `'/r'` aka `carriage return` will make the pointer back to the **start of line** and **overwrite** `flag` with `('lmao no flag for you ' * 32)`.  
That why when you run, it doesn't print the flag but only the lmao.  
Just add `cat -v` at the end to disable the function of `\r`.  
```bash
ssh hexed@challs.watctf.org -p 8022 | cat -v
```
> Flag: watctf{im_more_of_a_tram_fan_personally}

Peace!

