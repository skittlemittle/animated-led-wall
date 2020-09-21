# animated-led-wall
led wall that you can send animations to from a webapp
because mm yes

set the size of your panel in the arduino sketch
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

- `numFrames`:  2 bytes, 2 characters

- `framerate`: 2 bytes, 2 characters

- `+`: separates header from body

- `frame`:
  A list of hex color vals for the whole frame.
  Always end each frame with a trailing `#`

  `#ccff7d#00ff00#ffffff......#`

  The frames have to be as big as the panel or bad things happen

- `-`: separates frames
