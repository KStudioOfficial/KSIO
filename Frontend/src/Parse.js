// import fs from 'fs';
// import parse from 'parse-gp5';

const parse = require('parse-gp5');
const fs = require('fs');

const buf = fs.readFileSync(__dirname + '/tab.gp');
const tab = parse(buf);

console.log(tab);