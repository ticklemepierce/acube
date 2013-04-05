var that = this;

var Module = {
  'print': function report(str) {
    that.postMessage(str);
  }
};

importScripts('ACube.js');

this.addEventListener('message', function(e) {
  Module.cwrap('solve', 'void', ['string'])(e.data);
}, false);
