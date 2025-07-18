Description:  
A group of underground hackers might be using this legit site to communicate. Use your forensic techniques to uncover their message  
Hints:  
In the country that doesn't exist, the flag persists  

Open the web, i see so many flag as picture. `Ctrl + U` to view source code and checking, i see a country flag with diffirent details:  
<img width="1282" height="260" alt="image" src="https://github.com/user-attachments/assets/6cb7f66e-a239-4725-a0b0-f09b6f94cc3b" />  
Download the picture of the flag, i tried some steganography but didn't work. Then i found some code could do that either.  
```
from PIL import Image
import stepic

img = Image.open("<your_pic_here>")
data = stepic.decode(img)
print(data)

```  
Peace!

