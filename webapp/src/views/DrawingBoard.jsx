import React from 'react';
import './DrawingBoard.css';

export default class DrawingBoard extends React.Component {
  renderPixel(row, col) {
    return (
      <Pixel
        color={this.props.frame[row][col]}
        onClick={() => this.props.onClick(row, col)}
        key={row + col} // heck
      />
    );
  }

  render() {
    const frameHeight = 8;

    return (
      // ya i used index as the key, AMA
      // inb4 spaghetti
      <div className="drawing-board">
        {[...Array(frameHeight)].map((_, rowIndex) => (
          <div className="board-row" key={rowIndex}>
            {[...Array(frameHeight)].map((_, colIndex) => (
              this.renderPixel(rowIndex, colIndex)
            ))}
          </div>
        ))}
      </div>
    );
  }
}

// le pixels wow
function Pixel(props) {
  return (
    <button
      className="pixel"
      style={{ background: props.color }}
      onClick={props.onClick}
    >
    </button>
  );
}
