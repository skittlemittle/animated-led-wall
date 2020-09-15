// deals with the sequence data
// assumes that all frames have the same dimensions

class Board {
  constructor(width = 8, height = 8) {
    // list of frames
    this.width = width;
    this.height = height;
    this.frameIndex = 0;
    this.sequence = [];

    this.addFrame();
  }

  // appends a blank frame (all black)
  addFrame() {
    this.sequence.push(
      [...Array(this.height)].map((_, r) => (
        [...Array(this.width)].map((_, c) => (
          '#000'
        ))
      ))
    );
  }

  getFrame(index) {
    return this.sequence[index].slice();
  }

  removeFrame(index) {
    this.sequence.splice(index, 1);
  }

  // changes one pixel at a time aight
  editFrame(index, row, col, color) {
    this.sequence[index][row][col] = color;
  }

  get frameSequence() {
    return this.sequence.slice();
  }

  get sequenceLen() {
    return this.sequence.length;
  }

  get index() {
    return this.frameIndex;
  }

  set index(index) {
    this.frameIndex = index;
  }
}

export default Board;