class Toolbar {
  constructor() {
    // init stuff
    this.color = '#ff00ff';
    this.framerate = 10;
  }

  setColor(newColor) {
    this.color = newColor;
  }

  getColor() {
    return this.color;
  }

  setFramerate(framerate) {
    this.framerate = framerate;
  }

  getFramerate() {
    return this.framerate;
  }
}

export default Toolbar;