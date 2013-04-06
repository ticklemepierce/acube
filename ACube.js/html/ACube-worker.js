var that = this;

var Module = {
  'print': function report(str) {
    that.postMessage(str);
  }
};

importScripts('ACube.js');

var solve = Module.cwrap('solve', 'void', ['string']);
var set_opts = Module.cwrap('set_opts', 'void', ['string']);

this.addEventListener('message', function(e) {
  switch(e.data[0]) {
    case "solve":
      solve(e.data[1]);
      break;
    case "set_opts":
      set_opts(e.data[1]);
      break;
    default:
      Module.print("Bad message.");
      break;
  }
}, false);
