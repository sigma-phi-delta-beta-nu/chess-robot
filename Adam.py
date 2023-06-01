import serial
import time



MAX_BUFF_LEN = 255
port = serial.Serial("/dev/cu.usbserial-0001", 115200, timeout=1)


def task_chess():
    message = "home"
    port.write(message.encode())
    reading = ""
    while reading != "done":
        reading = port.readline()
        if reading != b'0\r\n':
            print(reading)
            time.sleep(.1)

def write_serial(cmd):
    cmd = cmd + '\n'
    port.write(cmd.encode())
task_chess()



