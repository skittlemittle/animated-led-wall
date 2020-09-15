/*
 * Simple color selector, just a grid of buttons.
 * Colors configured by passing as a list.
 */
import React from 'react'
import PixelGrid from './PixelGrid'

// AAAAAHAHAHAHAHAHAHAAHAHAHAHAHAHAHAHAHAHAHHHHAHAHAHA
// LKSRTHIOERUSTPERITVSERITVSREIUTSOVTITHOSEITOEITHIOTROTIRTOISETVOSIETHSO
const COLORS = [
  ['#8B0000', '#ff0000', '#ff0040', '#ff3333'], // red
  ['#ff4500', '#ffa500', '#ffff00', '#ffff66'], // orange
  ['#00ff00', '#7cfc00', '#80ff00', '#bfff00'], // green
  ['#0000ff', '#0080ff', '#00bfff', '#00ffff'], // blue
  ['#ff00bf', '#ff00ff', '#bf00ff', '#8000ff'], // "pink"
  ['#000000', '#696969', '#708090', '#ffffff'], // black to white
];

export class ColorSelector extends React.Component {
  selectColor(row, col) {
    this.props.onColorChange(COLORS[row][col]);
  }

  render() {
    return (
      <PixelGrid
        frame={COLORS}
        frameHeight={COLORS.length}
        frameWidth={COLORS[0].length}
        onClick={(row, col) => this.selectColor(row, col)}
      />
    );
  }
}
