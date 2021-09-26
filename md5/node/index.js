
const md5 = require('md5');
const fs = require('fs');

fs.readFile('../test', (_, buf) => {
    console.log(md5(buf));
});
