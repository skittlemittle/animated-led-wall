# animated-led-wall
led wall that you can send animations to from a webapp
because mm yes

note: only works on an 8x8 coz i went full chimp brain and hardcoded
a lot of garbage in the arduino sketch
# setting up

**the webapp**

- In `webapp/` run:

  ```shell
    npm install
    npm run build
  ```

- In `server/` make a python virtual env then run:

  ```shell
    pip install
    python app.py
  ```

  Edit `app.py` to set serial port

**Arduino bit**

- pin 3 to the led's data pin

- flash `ledwall/ledwall.ino` onto your arduino

## Animation command "protocol":

```
  RCV <size of message in number of characters>

  numFrames|framerate|+frame-frame-frame-frame

  #samples

  RCV 40
  0225+#ffffff#7dcc00-#ffffff#7dcc00#
```

- `numFrames`:  2 bytes

- `framerate`: 2 bytes

- `+`: separates header from body

- `frame`:
  A list of hex color vals for the whole frame.
  Always end each frame with a trailing `#`

  `#ccff7d#00ff00#ffffff......#`

- `-`: separates frames
