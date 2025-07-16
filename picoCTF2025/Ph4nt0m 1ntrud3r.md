Description:   
A digital ghost has breached my defenses, and my sensitive data has been stolen! 😱💻 Your mission is to uncover how this phantom intruder infiltrated my system and retrieve the hidden flag.
To solve this challenge, you'll need to analyze the provided PCAP file and track down the attack method. The attacker has cleverly concealed his moves in well timely manner. Dive into the network traffic, apply the right filters and show off your forensic prowess and unmask the digital intruder!  
Hints:  
Filter your packets to narrow down your search.  
Attacks were done in timely manner.  
Time is essential  

After open the PCAP file and read the number 3 hint, i sorted the traffic by time. 
Easy to see "TCP segment data" of some packets is Base64 because of the `==` tail.  
Make sure it in the order, decode it and you get the flag.  
Peace!


