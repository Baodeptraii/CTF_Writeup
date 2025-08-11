<img width="484" height="437" alt="image" src="https://github.com/user-attachments/assets/2beda13f-5459-4f3b-ba8f-4abea8570001" />   


Normal `nmap` not working, so i tried "maxium" scan i can on the site.  
```vim
sudo nmap -sS -sV -A -p- scanme.ctf.zone
```

Got lot of infomations after that :  
```bash
Not shown: 65495 closed tcp ports (reset)
PORT      STATE    SERVICE        VERSION
22/tcp    filtered ssh
2454/tcp  open     indx-dds?
3871/tcp  open     avocent-adsap?
7293/tcp  open     unknown
10962/tcp open     unknown
15160/tcp open     unknown
17983/tcp open     unknown
18395/tcp open     unknown
18728/tcp open     unknown
19185/tcp open     unknown
20447/tcp open     unknown
22258/tcp open     unknown
23990/tcp open     unknown
24196/tcp open     unknown
25161/tcp open     unknown
26525/tcp open     unknown
29115/tcp open     napster        WinMX or Lopster Napster P2P client
29172/tcp open     unknown
29762/tcp open     unknown
35486/tcp open     unknown
35725/tcp open     unknown
35943/tcp open     unknown
36650/tcp open     unknown
37299/tcp open     unknown
38897/tcp open     unknown
39461/tcp open     unknown
39961/tcp open     unknown
40632/tcp open     unknown
42747/tcp open     unknown
44426/tcp open     unknown
46045/tcp open     unknown
55283/tcp open     unknown
55305/tcp open     unknown
57932/tcp open     unknown
57937/tcp open     unknown
59220/tcp open     unknown
63931/tcp open     unknown
64199/tcp open     unknown
64471/tcp open     unknown
65534/tcp open     unknown
| fingerprint-strings:
|   DNSStatusRequestTCP, FourOhFourRequest, GenericLines, HTTPOptions, LPDString, NULL, RPCCheck, SSLSessionReq, TerminalServer, WMSRequest:
|_    Use the order of ports for the order of the flag!
9 services unrecognized despite returning data. If you know the service/version, please submit the following fingerprints at https://nmap.org/cgi-bin/submit.cgi?new-service :
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port2454-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r(
SF:NULL,1,"f")%r(GenericLines,1,"f")%r(RPCCheck,1,"f")%r(X11Probe,1,"f")%r
SF:(NotesRPC,1,"f")%r(giop,1,"f");
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port3871-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r(
SF:NULL,1,"l")%r(RPCCheck,1,"l")%r(DNSVersionBindReqTCP,1,"l")%r(TLSSessio
SF:nReq,1,"l")%r(LDAPBindReq,1,"l")%r(SIPOptions,1,"l")%r(LANDesk-RC,1,"l"
SF:)%r(TerminalServer,1,"l")%r(NCP,1,"l")%r(WMSRequest,1,"l")%r(ms-sql-s,1
SF:,"l");
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port7293-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r(
SF:NULL,1,"a")%r(DNSVersionBindReqTCP,1,"a")%r(Help,1,"a")%r(SSLSessionReq
SF:,1,"a")%r(LPDString,1,"a")%r(WMSRequest,1,"a")%r(oracle-tns,1,"a")%r(ms
SF:-sql-s,1,"a")%r(giop,1,"a");
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port10962-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r
SF:(NULL,1,"g")%r(GenericLines,1,"g")%r(HTTPOptions,1,"g")%r(RPCCheck,1,"g
SF:")%r(Help,1,"g")%r(SSLSessionReq,1,"g")%r(Kerberos,1,"g")%r(SMBProgNeg,
SF:1,"g")%r(X11Probe,1,"g")%r(LANDesk-RC,1,"g")%r(NCP,1,"g")%r(NotesRPC,1,
SF:"g")%r(ms-sql-s,1,"g")%r(afp,1,"g");
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port15160-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r
SF:(NULL,1,"{")%r(GenericLines,1,"{")%r(RPCCheck,1,"{")%r(DNSVersionBindRe
SF:qTCP,1,"{")%r(DNSStatusRequestTCP,1,"{")%r(Kerberos,1,"{")%r(SMBProgNeg
SF:,1,"{")%r(FourOhFourRequest,1,"{")%r(LANDesk-RC,1,"{")%r(JavaRMI,1,"{")
SF:%r(oracle-tns,1,"{");
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port17983-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r
SF:(NULL,1,"a")%r(GetRequest,1,"a")%r(RPCCheck,1,"a")%r(Help,1,"a")%r(SSLS
SF:essionReq,1,"a")%r(Kerberos,1,"a")%r(SMBProgNeg,1,"a")%r(X11Probe,1,"a"
SF:)%r(LANDesk-RC,1,"a")%r(NCP,1,"a")%r(NotesRPC,1,"a");
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port18395-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r
SF:(NULL,1,"0")%r(GenericLines,1,"0")%r(HTTPOptions,1,"0")%r(RTSPRequest,1
SF:,"0")%r(SSLSessionReq,1,"0")%r(TerminalServerCookie,1,"0")%r(TLSSession
SF:Req,1,"0")%r(LPDString,1,"0")%r(LDAPSearchReq,1,"0")%r(LANDesk-RC,1,"0"
SF:)%r(TerminalServer,1,"0");
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port18728-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r
SF:(NULL,1,"e")%r(GenericLines,1,"e")%r(GetRequest,1,"e")%r(RPCCheck,1,"e"
SF:)%r(DNSStatusRequestTCP,1,"e")%r(Help,1,"e")%r(SSLSessionReq,1,"e")%r(T
SF:LSSessionReq,1,"e")%r(SMBProgNeg,1,"e")%r(FourOhFourRequest,1,"e")%r(LD
SF:APBindReq,1,"e")%r(SIPOptions,1,"e");
==============NEXT SERVICE FINGERPRINT (SUBMIT INDIVIDUALLY)==============
SF-Port19185-TCP:V=7.94SVN%I=7%D=8/9%Time=6896A7D6%P=x86_64-pc-linux-gnu%r
SF:(NULL,1,"2")%r(GetRequest,1,"2")%r(HTTPOptions,1,"2")%r(RPCCheck,1,"2")
SF:%r(NotesRPC,1,"2")%r(JavaRMI,1,"2")%r(afp,1,"2");
Aggressive OS guesses: Linux 2.6.32 (88%), Linux 2.6.39 (88%), Linux 3.10 - 3.12 (88%), Linux 3.4 (88%), Linux 3.5 (88%), Linux 4.2 (88%), Linux 4.4 (88%), Synology DiskStation Manager 5.1 (88%), Linux 2.6.35 (87%), Linux 3.10 (87%)
No exact OS matches for host (test conditions non-ideal).
Network Distance: 20 hops

TRACEROUTE (using port 3306/tcp)
HOP RTT       ADDRESS
1   0.33 ms   TrqbNitro5.mshome.net (172.20.160.1)
2   1.64 ms   192.168.2.253 (192.168.2.253)
3   2.40 ms   192.168.1.1 (192.168.1.1)
4   ... 7
8   7.79 ms   10.255.10.122 (10.255.10.122)
9   28.06 ms  localhost (27.68.229.105)
10  27.47 ms  dynamic-ip-adsl.viettel.vn (125.212.189.93)
11  27.45 ms  unknown.telstraglobal.net (202.127.77.33)
12  ... 13
14  197.64 ms i-1001.ulco01.telstraglobal.net (202.84.178.69)
15  ... 19
20  209.91 ms ec2-52-211-134-167.eu-west-1.compute.amazonaws.com (52.211.134.167)

OS and Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 1221.20 seconds

```

Do you see this part ?  

```vim
| fingerprint-strings:
|   DNSStatusRequestTCP, FourOhFourRequest, GenericLines, HTTPOptions, LPDString, NULL, RPCCheck, SSLSessionReq, TerminalServer, WMSRequest:
|_    Use the order of ports for the order of the flag!
```

Yeah, that what we want.  
Small script to list all the ports and connect each characters to get the flag.  

```bash
#!/bin/bash
ports=(2454 3871 7293 10962 15160 17983 18395 18728 19185 20447 22258 23990 24196 25161 26525 29115 29172 29762 35486 35725 35943 36650 37299 38897 39461 39961 40632 42747 44426 46045 55283 55305 57932 57937 59220 63931 64199 64471 65534)

flag=""
for port in "${ports[@]}"; do
    char=$(echo "" | nc scanme.ctf.zone "$port" 2>/dev/null)
    flag+="$char"
    echo "Port $port: $char"
done

echo "Flag: $flag"
```

```bash
chmod +x get_flag.sh
./get_flag.sh
```

Peace!



