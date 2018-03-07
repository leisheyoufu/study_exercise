var Terminal = require('xterm').Terminal;
Terminal.applyAddon(require('xterm/lib/addons/fit'));

var terminalContainer = document.getElementById('term-box');
term = new Terminal({
    cursorBlink: true
});
term.open(terminalContainer);
term.fit();
var viewport = document.querySelector('.xterm-viewport');

function log() {
    console.log(
        term.cols,
        term.rows,
        viewport.style.lineHeight,
        viewport.style.height
    );
}


log();

term.writeln('this is demo for "refresh-viewport-height"!');
term.writeln('press any key!');
log();

term.on('key', function(key, ev) {
    // let's change the line-height!
    terminalContainer.style.lineHeight = '20px';
    term.fit();

    for (var i = 1; i <= 10; i++) {
        term.writeln(i);
    }
    term.write('can see this line?');

    log();
});