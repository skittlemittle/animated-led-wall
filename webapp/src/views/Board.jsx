// drawing board & next prev buttons
import React from 'react'
import PixelGrid from './PixelGrid'

export default class Board extends React.Component {
  render() {
    return (
      <PixelGrid
        frame={this.props.frame}
        frameHeight={this.props.frame.length}
        frameWidth={this.props.frame[0].length}
        onClick={(row, col) => this.props.onBoardClick(row, col)}
      />
    );
  }
}