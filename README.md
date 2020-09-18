# animated-led-wall
led wall that you can send animations to from a webapp
because mm yes

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

  Edit app.py to set serial port

**Arduino bit**

- flash ledwall/ledwall.ino onto your arduino

## Animation command "protocol":

```
  RCV <size of message in number of characters>

  numFrames|framerate|+frame-frame-frame-frame

  #samples

  RCV 40
  0225+[#ffffff,#7dcc00]-[#ffffff,#7dcc00]
```

- `numFrames`:  2 bytes

- `framerate`: 2 bytes

- `+`: separates header from body

- `frame`:
  A list of hex color vals for the whole frame.

  `#ccff7d#00ff00#ffffff......`

- `-`: separates frames