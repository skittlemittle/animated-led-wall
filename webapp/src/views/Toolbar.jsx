// le toolbar innit
import React from 'react';
import './Toolbar.css';

export default function Toolbar(props) {
  return (
    <div className="toolbar">
      <ColorSelector />
      <ColorIndicator color={props.indicatorColor} />
      <FrameRateInput framerate={props.framerate} />
      <UploadButton onClick={() => props.onUploadClick()} />
    </div>
  );
}

function ColorSelector() {
  return (
    <div className="color-selector">
    </div>
  );
}

// TODO: proto just a bunch of buttons
function ColorIndicator(props) {
  const curColor = props.color;
  return (
    <div
      className="color-indicator"
      style={{ minHeight: '20', background: { curColor }, margin: '5px' }}
    >
      <p></p>
    </div>
  );
}

function FrameRateInput(props) {
  return (
    <div className="framerate-input">
      <legend>framerate:</legend>
      <input
        type="text"
        value={props.framerate}
        defaultValue={props.framerate}
        onChange={props.onFramerateChange}
      />
    </div>
  );
}

function UploadButton(props) {
  return (
    <button
      className="upload-button"
      onClick={props.onClick}
    >
      Play &rarr;
    </button>
  );
}