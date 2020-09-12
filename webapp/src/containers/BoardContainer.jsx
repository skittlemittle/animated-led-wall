import React from 'react';

import { AppState } from '../views/App';
import DrawingBoard from '../views/DrawingBoard'

export default class BoardContainer extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      frame: AppState.board.getFrame(0)
    };
  }

  onBoardClick(row, col) {
    const frameIndex = 0;
    const color = AppState.toolbar.getColor();
    const frame = this.state.frame.slice();
    // edit le frame
    frame[row][col] = color;
    AppState.board.editFrame(frameIndex, row, col, color);
    this.setState({ frame: AppState.board.getFrame(frameIndex) });
  }

  render() {
    return (
      <DrawingBoard
        frame={this.state.frame}
        onClick={(row, col) => this.onBoardClick(row, col)}
      />
    );
  }
}