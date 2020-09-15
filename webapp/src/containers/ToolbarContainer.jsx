import React from 'react'

import { AppState } from '../views/App'
import Toolbar from '../views/Toolbar'

export default class ToolbarContainer extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      color: AppState.toolbar.color,
      framerate: AppState.toolbar.framerate
    };

    this.handleFrameRateChange = this.handleFrameRateChange.bind(this);
    this.handleUploadButton = this.handleUploadButton.bind(this);
    this.handleColorChange = this.handleColorChange.bind(this);
  }

  handleUploadButton() {
    // get global sequence
    const sequence = AppState.board.frameSequence;
    console.log(sequence);
    // send it to the arduino
  }

  handleColorChange(color) {
    AppState.toolbar.color = color;
    this.setState({ color: AppState.toolbar.color })
  }

  handleFrameRateChange(framerate) {
    framerate = parseInt(framerate);
    if (isNaN(framerate)) return;

    AppState.toolbar.framerate = framerate;
    this.setState({ framerate: AppState.toolbar.framerate });
  }

  render() {
    return (
      <Toolbar
        indicatorColor={this.state.color}
        defFramerate={this.props.defFramerate}
        onColorChange={(c) => this.handleColorChange(c)}
        onFramerateChange={(f) => this.handleFrameRateChange(f)}
        onUploadClick={this.handleUploadButton}
      />
    );
  }
}