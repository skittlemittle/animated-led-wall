// deals with the sequence data

class Board {
  constructor() {
    // list of frames
    this.frameIndex = 0;
    this.sequence = [
      [
        [-1, '#00ff40', -1, '#7D00FF', '#7D00FF', -1, '#00ff40', -1],
        ['#00ff40', -1, '#7D00FF', '#ffff00', '#ffff00', '#7D00FF', -1, '#00ff40'],
        [-1, '#7D00FF', '#ffff00', -1, -1, '#ffff00', '#7D00FF', -1],
        ['#7D00FF', '#ffff00', -1, -1, -1, -1, '#ffff00', '#7D00FF'],
        ['#7D00FF', '#ffff00', -1, -1, -1, -1, '#ffff00', '#7D00FF'],
        [-1, '#7D00FF', '#ffff00', -1, -1, '#ffff00', '#7D00FF', -1],
        ['#00ff40', -1, '#7D00FF', '#ffff00', '#ffff00', '#7D00FF', -1, '#00ff40'],
        [-1, '#00ff40', -1, '#7D00FF', '#7D00FF', -1, '#00ff40', -1]
      ]
    ];
  }

  getSequence() {
    return this.sequence.slice();
  }

  addFrame(frame) {
    this.sequence.push(frame);
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
}

export default Board;