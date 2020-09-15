import React from 'react'

import './styles/App.css'
import ToolbarContainer from '../containers/ToolbarContainer'
import BoardContainer from '../containers/BoardContainer'
import Board from '../models/Board'
import Toolbar from '../models/Toolbar'

// genius yes i know
export const AppState = {
  board: new Board(),
  toolbar: new Toolbar()
}

export class App extends React.Component {
  render() {
    return (
      <div className="App">
        <ToolbarContainer defFramerate={AppState.toolbar.getFramerate()}/>
        <BoardContainer />
      </div>
    );
  }
}