Description:  
This service provides you an encrypted flag. Can you decrypt it with just N & e?  
Hints:  
How much do we trust randomness?  
Notice anything interesting about N?  
Try comparing N across multiple requests  

Tbh i have nothing to say about this challenge...  

```python
from Crypto.Util.number import long_to_bytes

N = <given_even_N>
e = 65537

q = N // 2
phi_N = q - 1
d = pow(e, -1, phi_N)

c = <given_ciphertext>
m = pow(c, d, N)
flag = long_to_bytes(m)
print(flag)
```  

Peace!



