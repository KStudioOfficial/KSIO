import logo from './logo.svg';
import './App.css';

import React, { useEffect, useState } from 'react';

import * as Juce from "./juceAPI/index"

function App() {

    const [state, setState] = useState("hello");

    useEffect(() => {
        setState(window.__JUCE__.initialisationData);
    }, []);

    console.log(window.__JUCE__.backend);
    window.__JUCE__.backend.addEventListener(
        "exampleEvent",
        (objectFromCppBackend) => {
            console.log(objectFromCppBackend);
        }
    )

    return (
        <div className="App">
        <header className="App-header">
            <img src={logo} className="App-logo" alt="logo" />
            <p>
            {state.testDataField}
            </p>
            <a
            className="App-link"
            href="https://reactjs.org"
            target="_blank"
            rel="noopener noreferrer"
            >
            Learn React
            </a>
        </header>
        </div>
    );
}

export default App;
