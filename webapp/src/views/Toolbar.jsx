// le toolbar innit
import React from 'react'
import './styles/Toolbar.css'
import { ColorSelector } from './ColorSelector'

export default function Toolbar(props) {
  return (
    <div className="toolbar">
      <ColorSelector onColorChange={(c) => props.onColorChange(c)} />
      <ColorIndicator color={props.indicatorColor} />
      <FrameRateInput
        defFramerate={props.defFramerate}
        onChange={(e) => props.onFramerateChange(e.target.value)}
      />
      <UploadButton onClick={() => props.onUploadClick()} />
    </div>
  );
}

function ColorIndicator(props) {
  return (
    <div
      className="color-indicator"
      style={{ minHeight: '20', background: props.color, margin: '5px' }}
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
        defaultValue={props.defFramerate}
        onChange={props.onChange}
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