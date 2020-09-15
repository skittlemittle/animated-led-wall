/*
 * Makes a grid of colored buttons from passed frames
 * frames are assumed to be rectangle/square 2D arrays
 */
import React from 'react'
import './styles/PixelGrid.css'

export default class PixelGrid extends React.Component {
  renderPixel(row, col) {
    return (
      <PixelButton
        color={this.props.frame[row][col]}
        onClick={() => this.props.onClick(row, col)}
        key={row + col} // heck
      />
    );
  }

  render() {
    return (
      // ya i used index as the key, AMA
      // inb4 spaghetti
      <div className="drawing-board">
        {[...Array(this.props.frameHeight)].map((_, rowIndex) => (
          <div className="board-row" key={rowIndex}>
            {[...Array(this.props.frameWidth)].map((_, colIndex) => (
              this.renderPixel(rowIndex, colIndex)
            ))}
          </div>
        ))}
      </div>
    );
  }
}

// le pixels wow
function PixelButton(props) {
  return (
    <button
      className="pixel"
      style={{ background: props.color }}
      onClick={props.onClick}
    >
    </button>
  );
}
