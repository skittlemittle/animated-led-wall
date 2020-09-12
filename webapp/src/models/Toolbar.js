class Toolbar {
  constructor() {
    // init stuff
    this.currColor = '#000000';
    this.framerate = 10;
  }

  setColor(newColor) {
    this.currColor = newColor;
  }

  getColor() {
    return this.currColor;
  }

  setFramerate(framerate) {
    this.framerate = framerate;
  }

  getFramerate() {
    return this.framerate;
  }
}

export default Toolbar;