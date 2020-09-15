import React from 'react'

import { AppState } from '../views/App'
import Toolbar from '../views/Toolbar'

export default class ToolbarContainer extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      color: AppState.toolbar.getColor(),
      framerate: AppState.toolbar.getFramerate()
    };

    this.handleFrameRateChange = this.handleFrameRateChange.bind(this);
    this.handleUploadButton = this.handleUploadButton.bind(this);
    this.handleColorChange = this.handleColorChange.bind(this);
  }

  handleUploadButton() {
    // get global sequence
    const sequence = AppState.board.getSequence();
    console.log(sequence);
    // send it to the arduino
  }

  handleColorChange(color) {
    AppState.toolbar.setColor(color);
    this.setState({ color: AppState.toolbar.getColor() })
  }

  handleFrameRateChange(framerate) {
    framerate = parseInt(framerate);
    if (isNaN(framerate)) return;

    AppState.toolbar.setFramerate(framerate);
    this.setState({ framerate: AppState.toolbar.getFramerate() });
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