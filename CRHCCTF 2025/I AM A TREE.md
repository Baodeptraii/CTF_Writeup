<img width="495" height="403" alt="image" src="https://github.com/user-attachments/assets/0ce76174-b618-4778-9981-8d4343c156f2" />  

A tree ? A branch ? That `git` chall for sure !  
Download and extract it, run some `git` command:  
```
┌──(trqb㉿TrqbNitro5)-[/mnt/e/CTF/hey/hey]
└─$ git reflog
a8a9ab9 (HEAD, flag-branch) HEAD@{0}: checkout: moving from main to a8a9ab9
0accb0f (main) HEAD@{1}: checkout: moving from flag-branch to main
a8a9ab9 (HEAD, flag-branch) HEAD@{2}: checkout: moving from main to flag-branch
0accb0f (main) HEAD@{3}: commit: hey
f3f60b2 HEAD@{4}: checkout: moving from flagWOW to main
f1b7879 (flagWOW) HEAD@{5}: commit: IDK
f3f60b2 HEAD@{6}: checkout: moving from main to flagWOW
f3f60b2 HEAD@{7}: checkout: moving from flag-branch to main
a8a9ab9 (HEAD, flag-branch) HEAD@{8}: checkout: moving from main to flag-branch
f3f60b2 HEAD@{9}: checkout: moving from flag-branch to main
a8a9ab9 (HEAD, flag-branch) HEAD@{10}: commit: Add FLAG.txt
f3f60b2 HEAD@{11}: checkout: moving from main to flag-branch
f3f60b2 HEAD@{12}: commit (initial): main

┌──(trqb㉿TrqbNitro5)-[/mnt/e/CTF/hey/hey]
└─$ git checkout -f a8a9ab9
HEAD is now at a8a9ab9 Add FLAG.txt

┌──(trqb㉿TrqbNitro5)-[/mnt/e/CTF/hey/hey]
└─$ ls
flag.py  FLAG.txt  placeholder.txt

┌──(trqb㉿TrqbNitro5)-[/mnt/e/CTF/hey/hey]
└─$ cat what ???
```
Peace!


