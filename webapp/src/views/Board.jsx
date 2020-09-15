// drawing board & next prev buttons
import React from 'react'
import PixelGrid from './PixelGrid'
import './styles/Board.css'

export default class Board extends React.Component {
  render() {
    return (
      <div className="board">
        <ArrowButton
          symbol={'<'}
          onClick={() => this.props.onArrowClick('L')}
        />
        <PixelGrid
          frame={this.props.frame}
          frameHeight={this.props.frame.length}
          frameWidth={this.props.frame[0].length}
          onClick={(row, col) => this.props.onBoardClick(row, col)}
        />
        <ArrowButton
          symbol={'>'}
          onClick={() => this.props.onArrowClick('R')}
        />
      </div>
    );
  }
}

function ArrowButton(props) {
  return (
    <button
      className="arrow-button"
      onClick={props.onClick}
    >
      {props.symbol}
    </button>
  );
}