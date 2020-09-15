import React from 'react'

import { AppState } from '../views/App'
import Board from '../views/Board'

export default class BoardContainer extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      frame: AppState.board.getFrame(0)
    };
    this.handleBoardClick = this.handleBoardClick.bind(this);
  }

  handleBoardClick(row, col) {
    const frameIndex = 0;
    const color = AppState.toolbar.getColor();
    // edit le frame
    AppState.board.editFrame(frameIndex, row, col, color);
    this.setState({ frame: AppState.board.getFrame(frameIndex) });
  }

  render() {
    return (
      < Board
        frame={this.state.frame}
        onBoardClick={(row, col) => this.handleBoardClick(row, col)}
      />
    );
  }
}