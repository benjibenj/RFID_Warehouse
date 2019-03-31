import serial
import datetime

ser = serial.Serial("/dev/ttyUSB0", 115200)
# Connect with Raspberry Pi

with open("RFIDtrace.txt", "ab") as f:
    for x in range(10):
        # get tag id thought serial port
        line = ser.readline().decode("utf-8")
        print(line)
        if line.startswith(" [TAG READ]"):
            f.write(
                datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f").encode("utf-8")
            )
            f.write(ser.readline())
