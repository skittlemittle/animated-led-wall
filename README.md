# animated-led-wall
led wall that you can send animations to

## Animation format:

```
  RCV <size of message in number of characters>
  numFrames|frameRate|list_of_frame_sizes+x,y,r,g,b-x,y,r,g,b,x,y,r,g,b-

  #samples
  RCV 53
  02331010+0,0,255,0,0,1,1,0,0,0-0,0,0,0,0,1,1,255,0,0-

  RCV 49
  03021005+4,4,127,50,6,6,0,125,50,100-7,2,0,255,0-
```

- numFrames:  2 bytes

- frameRate: 2 bytes

- list_of_frame_sizes: 2 bytes each entry

- +: separates header from body

- packets: `x,y,r,g,b`

- -: separates frames

- ,: separates packet entries