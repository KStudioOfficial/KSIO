import {useCallback, useEffect, useState} from "react";
import fs from 'fs';

const parse = require('parse-gp5');
// const fs = require('fs');

export const AppTwo = () => {
    const [buffer, setBuffer] = useState(null);

    const readFile = async () => {
        try {
            const response = await fetch('tab.gp'); // Fetch the file
            const arrayBuffer = await response.arrayBuffer(); // Get the file as ArrayBuffer
            const fileBuffer = Buffer.from(arrayBuffer); // Create a Buffer from ArrayBuffer
            setBuffer(fileBuffer);
        } catch (error) {
            console.error('Error reading file:', error);
        }
    };

    const doGp5Parse = useCallback(() => {
        const buf = fs.readFileSync(__dirname + './tab.gp');
        // const buf = readFile();
        const tab = parse(buf);

        console.log(tab);
    }, []);

    useEffect(() => {
        console.log("The useEffect is running");
        doGp5Parse();
    }, [doGp5Parse]);

    return (
        <div>
            <p>This is another component</p>
        </div>
    )
}