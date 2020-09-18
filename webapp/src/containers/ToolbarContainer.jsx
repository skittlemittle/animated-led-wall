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

  // send animation to the arduino
  async handleUploadButton() {
    const data = {
      framerate: AppState.toolbar.framerate,
      sequence: AppState.board.frameSequence
    };

    const options = {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(data)
    };

    const response = await fetch('/upload', options);
    console.log(await response.json());
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