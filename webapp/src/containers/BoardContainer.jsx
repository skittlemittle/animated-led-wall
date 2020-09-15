import React from 'react'

import { AppState } from '../views/App'
import Board from '../views/Board'

export default class BoardContainer extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      frame: AppState.board.getFrame(AppState.board.index)
    };
    this.handleBoardClick = this.handleBoardClick.bind(this);
  }

  handleBoardClick(row, col) {
    const frameIndex = AppState.board.index;
    const color = AppState.toolbar.color;
    // edit le frame
    AppState.board.editFrame(frameIndex, row, col, color);
    this.setState({ frame: AppState.board.getFrame(frameIndex) });
  }

  // next/previous frame buttons
  handleArrowClick(direction) {
    let index = AppState.board.index;

    if (direction === 'L' && index > 0) {
      index -= 1;
    } else if (direction === 'R') {
      index += 1;
    }
    AppState.board.index = index;
    // just add frames when needed
    if (AppState.board.sequenceLen < index + 1) {
      AppState.board.addFrame();
    }
    // update state
    this.setState({ frame: AppState.board.getFrame(AppState.board.index) });
  }

  render() {
    return (
      < Board
        frame={this.state.frame}
        onBoardClick={(row, col) => this.handleBoardClick(row, col)}
        onArrowClick={(direction) => this.handleArrowClick(direction)}
      />
    );
  }
}