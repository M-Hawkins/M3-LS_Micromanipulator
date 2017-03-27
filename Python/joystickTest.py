import serial

ser = serial.Serial('/dev/ttyACM1', 9600)

alternate = True

while True:
    rec = ser.readline()
    if (rec[0] == "U"):
        if (alternate):
            ser.write(b'B7')
            alternate = False
        else:
            ser.write(b'J124578')
            alternate = True
    else:
        print(rec)