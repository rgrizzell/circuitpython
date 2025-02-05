import floppyio

mfm_content = (
    b"HHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHH"
    b"H00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH0"
    b"0HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00H"
    b"HHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHH"
    b"H00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH0"
    b"0HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00H"
    b"HHH00HHHH00HHHH00HHHH00HHHH00HHHH00H00000000000000000000000000"
    b"00000000000000000000000000000000000000000000000000000000000000"
    b"0000000H0H`H`0H`H`0H`H`00000H0HHH00HHHH00HHHH00HHHH00HHHH00HHH"
    b"H00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH0"
    b"0HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00H"
    b"HHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHH"
    b"H00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH0"
    b"0HHHH00HHHH00HHHH00H000000000000000000000000000000000000000000"
    b"00000000000000000000000000000000000000000000000000000H`H`H0`H`"
    b"H0`H`H0000000H0000000000000000000000HH0000H`0HH`HH0`000`HH00HH"
    b"HH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH"
    b"00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00HHHH00"
    b"H0000000000000000000000000000000000000000000000000000000000000"
    b"0000000000000000000000000000000000H`H`H0`H`H0`H`H00000`0`0H00H"
    b"`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0"
    b"HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HH"
    b"H0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0H"
    b"H0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0"
    b"H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H0"
    b"0H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H"
    b"`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0"
    b"HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH"
    b"0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0"
    b"H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0"
    b"H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H0"
    b"0H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H"
    b"`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0"
    b"HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HH"
    b"H0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0H"
    b"H0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0"
    b"H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H0"
    b"0H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H"
    b"`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0"
    b"HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH"
    b"0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0"
    b"H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0"
    b"H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H0"
    b"0H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H"
    b"`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0"
    b"HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HH"
    b"H0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0H"
    b"H0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0"
    b"H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H0"
    b"0H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H"
    b"`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0"
    b"HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH"
    b"0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0"
    b"H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0"
    b"H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H0"
    b"0H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H"
    b"`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0"
    b"HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HH"
    b"H0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0H"
    b"H0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0"
    b"H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H0"
    b"0H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H"
    b"`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0"
    b"HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH"
    b"0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0"
    b"H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0"
    b"H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H0"
    b"0H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H"
    b"`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0HH0HH0H00H`0HHH0H0H00H`0"
    b"HH0HH0H00H`0HHH0H0H00H`0HH0``HHHH0`0000hhhhhhhhhhhhhhhhhhhhhhh"
)

b = bytearray(512)
r = floppyio.mfm_readinto(b, mfm_content, 60, 84)
print(r)
print(b)
