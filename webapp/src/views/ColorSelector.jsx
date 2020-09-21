/*
 * Simple color selector, just a grid of buttons.
 * Colors configured by passing as a list.
 */
import React from 'react'
import PixelGrid from './PixelGrid'

// AAAAAHAHAHAHAHAHAHAAHAHAHAHAHAHAHAHAHAHAHHHHAHAHAHA
// LKSRTHIOERUSTPERITVSERITVSREIUTSOVTITHOSEITOEITHIOTROTIRTOISETVOSIETHSO
const COLORS = [
  ['#ff0000', '#ff8000', '#ffbf00', '#ffff00'],
  ['#bfff00', '#80ff00', '#40ff00', '#00ff00'],
  ['#00ff40', '#00ff80', '#00ffbf', '#00ffff'],
  ['#00bfff', '#0080ff', '#0040ff', '#0000ff'],
  ['#4000ff', '#8000ff', '#bf00ff', '#ff00ff'],
  ['#ff00bf', '#ff0080', '#ff0040', '#ec1313'],
  ['#000000', '#e0ffff', '#00fa9a', '#ffffff'],
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
