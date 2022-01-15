
const md5File = require('md5-file');
const fs = require('fs');

fs.readdir('../files', (err, files) => {
    files.forEach(file => {
        let hash = md5File.sync('../files/' + file);
        console.log(hash, file);
    })
});
