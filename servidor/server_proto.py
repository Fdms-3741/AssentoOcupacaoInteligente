import os
import socketserver


# Import platform-specific functions to lock screen
if os.name == 'nt':
    import ctypes
if os.name == 'posix':
    import subprocess
    import dbus

#
# Globals
#
secret_code = "Never Gonna Give You Up"
secret_response = "Never gonna let you down"
serverPort = 33245

posixLockCommands = [
    ["qdbus", "org.freedesktop.ScreenSaver", "/ScreenSaver", "Lock"],
    ['qdbus-qt5',"org.freedesktop.ScreenSaver","/ScreenSaver","Lock"]
]

def LockScreen():
    if os.name == 'nt':
        ctypes.windll.user32.LockWorkStation()
    if os.name == 'posix':
        for attempt in posixLockCommands:
            try:
                result = subprocess.run(attempt)
                return
            except:
                pass
        raise Exception("Couldn't lock screen")

class ServerHandler(socketserver.BaseRequestHandler):
    def handle(self):
        data = self.request[0].strip()[:len(secret_code)].decode('ascii')
        socket = self.request[1]
        print(f"received '{data}' from {self.client_address[0]}")
        if data == secret_code:
            print(f"Code matched. Sending response '{secret_response}'")
            socket.sendto(bytes(secret_response,'ascii'),self.client_address)
            LockScreen()


if __name__ == "__main__":
    with socketserver.UDPServer(('0.0.0.0',serverPort),ServerHandler) as server:
        server.serve_forever()
