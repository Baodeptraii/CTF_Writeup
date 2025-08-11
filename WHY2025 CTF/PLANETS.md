<img width="482" height="517" alt="image" src="https://github.com/user-attachments/assets/d1c4f90b-d0fb-481f-8c8c-e8dc3d94d7a4" />  

Open website and Ctrl U to view source code. This part is a vulnerable :  

<img width="709" height="211" alt="image" src="https://github.com/user-attachments/assets/ffcc0e22-aa60-4a4a-8cc9-34d877e6c2f6" />  

Client send QUERY directly into `./api.php` without filter => easly to SQLi.  
Let's try some.  

<img width="767" height="267" alt="image" src="https://github.com/user-attachments/assets/112c86ab-2341-47e6-93e2-4a1db8441a50" />  

That true !  

<img width="1113" height="282" alt="image" src="https://github.com/user-attachments/assets/612073b9-ff0d-4ced-b931-7a222d91a7ce" />  

Peace!





