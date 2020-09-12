import React from 'react';

import { AppState } from '../views/App';
import Toolbar from '../views/Toolbar'

export default class ToolbarContainer extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      color: -1
    };
  }

  handleUploadButton() {
    console.log("UPLOAD");
    // get global sequence
    // send it to the arduino
  }

  handleColorChange() {
    // set global color
    // update color indicator
  }

  handleFrameRateChange() {
    // set global frameRate
    // update input val?
  }

  render() {
    return (
      <Toolbar
        indicatorColor={this.state.color}
        framerate={this.state.framerate}
        onFramerateChange={this.handleFrameRateChange()}
        onUploadClick={() => this.handleUploadButton()}
      />
    );
  }
}