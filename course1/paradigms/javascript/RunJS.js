// Node.js compatible runner


"use strict";

var context = {
    println: function() {
        console.log(Array.prototype.map.call(arguments, String).join(' '));
    },
    print: function() {
        process.stdout.write(Array.prototype.map.call(arguments, String).join(' '));
    },
    eval: function(script, file) {
        return require("vm").runInNewContext(script, context, file || "eval");
    },
    include: function(file) {
        context.eval(require("fs").readFileSync(file));
    }
};

context.include("script.js");
