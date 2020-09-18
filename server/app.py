# just sends animations to the arduino

from flask import Flask, request, jsonify
import serial
import json
import math
import os


def generateCommand(content):
    numFrames = 0
    frames = ""

    # pogchamp
    for fr in content["sequence"]:
        numFrames += 1
        for row in fr:
            for pixel in row:
                frames += pixel
        frames += "-"

    cmd = f"{numFrames:02}{content['framerate']}+{frames}"
    return cmd


class Serial:
    def __init__(self, port="/dev/USB0", rate=9600, timeout=10):
        self._serial = serial.Serial(port, rate, timeout=timeout)
        self.cmdChunkSize = 128.0 # arduino serial buffer size

    def _shortCmd(self, cmd):
        self._serial.write(cmd)
        return self._serial.readline().strip()

    # takes strings chops em up and makes _shortCmd send them
    def _longCmd(self, cmd):
        response = self._shortCmd("RCV " + str(len(cmd)) + "\n")
        if response != 'RDY':
            return None

        for i in range(int(math.ceil(len(cmd) / self.cmdChunkSize))):
            c = cmd[128 * i : 128 * (i + 1)]
            response = self._shortCmd(c)
        return self._serial.readline().strip()
    
    def command(self, cmd):
        if len(cmd) < 128:
            response = self._shortCmd(cmd + "\n")
        else:
            response = self._longCmd(cmd)
        return response


# flask flask
app = Flask(__name__, static_folder="../webapp/build/", static_url_path="/")

@app.route("/")
def index():
    return app.send_static_file("index.html")


@app.route("/upload", methods=["POST"])
def handleRequest():
    content = request.json
    cmd = generateCommand(content)
    print(cmd)
    serial = Serial(port='/dev/USB0', rate='115200') # have fun manually setting port
    res = serial.command(cmd)

    if res == cmd:
        return jsonify("sucess")
    else:
        return jsonify("heck")


if __name__ == "__main__":
    app.run(port=8000, debug=False)
