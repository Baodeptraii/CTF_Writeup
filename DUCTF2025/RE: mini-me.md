<img width="1150" height="553" alt="image" src="https://github.com/user-attachments/assets/2ec59579-2f8f-47c7-9c9f-46c562fc990b" />  

Using `Ctrl + U` to read the source code, checking JS file and we see the hidden.  

<img width="939" height="331" alt="image" src="https://github.com/user-attachments/assets/97cc36fa-f3cc-4e72-b982-965d8b4c9e98" />  

Put it in to URL ( keep the `static/js` ) to download it.  We receive a JS file which be obfucated. I used "AI generated" to see and i receive a script.  
Run the script with dev tool and receive a key:  `TUNG-TUNG-TUNG-TUNG-SAHUR` 

<img width="822" height="392" alt="image" src="https://github.com/user-attachments/assets/a48acd7a-8040-40b0-aa15-c673cca2dfa1" />  

Read the source code chall given, we can see:  

<img width="519" height="186" alt="image" src="https://github.com/user-attachments/assets/ae1f3020-5733-4f8b-afe3-1699e10b20d4" />  

Let's try to POST this key the server : `curl -X POST https://web-mini-me-ab6d19a7ea6e.2025.ductf.net/admin/flag -H "X-API-Key: TUNG-TUNG-TUNG-TUNG-SAHUR"`  

We have the flag !  

Peace!




