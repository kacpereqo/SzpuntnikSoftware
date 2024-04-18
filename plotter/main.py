import configparser

import serial
import serial.tools.list_ports
import uvicorn
from fastapi import FastAPI, WebSocket

app = FastAPI()

@app.websocket("/ws")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    config = configparser.ConfigParser()
    config.read('platformio.ini')

    env_name = config.sections()[0].split(':')[1].replace('_', ' ')
    port = None

    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        if p.product is None: 
            continue
        if p.product.lower() == env_name:
            port = p.device

    if port is None:
        print("No device found")
    else:
        print(f"Found device at {port}")

    ser = serial.Serial(port, 115200)
    print("Connected to serial port")
    while True:
        data = ser.readline().decode('utf-8').strip()
        await websocket.send_text(data)


if __name__ == "__main__":
    uvicorn.run("main:app", reload=True)