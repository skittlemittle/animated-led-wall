class Toolbar {
  constructor() {
    // init stuff
    this.curColor = '#ff00ff';
    this.curFramerate = 10;
  }

  set color(newColor) {
    this.curColor = newColor;
  }

  get color() {
    return this.curColor;
  }

  set framerate(framerate) {
    this.curFramerate = framerate;
  }

  get framerate() {
    return this.curFramerate;
  }
}

export default Toolbar;