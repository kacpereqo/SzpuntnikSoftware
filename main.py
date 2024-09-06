import serial
import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
for idx,(port, desc, hwid) in enumerate(ports):
    print(f"[{idx}] {port}: {desc} [{hwid}]")

chosen_port = int(input("Select port: "))


ser = serial.Serial(ports[chosen_port][0], baudrate=9600, timeout=3)
print("connected")

print("[1] print")
print("[2] save to file")
mode = int(input("Enter mode: "))


while True:
    try:
        if mode == 1:
            print(ser.readline().decode().strip())
        else:
            with open("data.txt", "a") as f:
                f.write(ser.readline().decode().strip() + "\n")
    except KeyboardInterrupt:
        break   
ser.close()

