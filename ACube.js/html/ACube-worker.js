var that = this;

var iniResolveFn;
var iniPromise = new Promise(function(resolve, reject) {
  iniResolveFn = resolve;
});;

var Module = {
  'print': function report(str) {
    that.postMessage(str);
  },
  'printErr': function report(str) {
    that.postMessage(str);
  },
  'onRuntimeInitialized': function() {
    iniResolveFn();
  }
};

importScripts('ACube.js');

var solve = Module.cwrap('solve', 'void', ['string']);
var set_opts = Module.cwrap('set_opts', 'void', ['string']);

this.addEventListener('message', function(e) {
  iniPromise.then(function() {
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
  });
}, false);
