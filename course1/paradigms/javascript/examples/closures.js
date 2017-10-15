"use strict";

chapter("Closures");

function incrementor(step) {
    var n = 0;
    return function() {
        n += step;
        return n;
    }
}

var inc = incrementor(10);
println("n and step are captured in closure");
println("    inc() = " + inc());
println("    inc() = " + inc());
println("    inc() = " + inc());

println("adders1 shares same i:");
function adders1(n) {
    var a = [];
    for (var i = 0; i < n; i++) {
        a.push(function(v) { return i + v; });
    }
    return a;
}

a = adders1(3);
for (j = 0; j < a.length; j++) {
    println("    adders1[" + j + "] adds " + a[j](0));
}

println("adders2 has a copy of i named w:");
function adders2(n) {
    var a = [];
    for (var i = 0; i < n; i++) {
        a.push(
            (function(w) {
                return function(v) { return w + v; }
            })(i) // Call of declared lambda
        );
    }
    return a;
}

var a = adders2(3);
for (var j = 0; j < a.length; j++) {
    println("    adders2[" + j + "] adds " + a[j](0));
}
println();

println("Points is module reference");
var points = (function() {
    var name = "hello";
    function Point(x, y) {
        println("Constructor called");
        var z = 0;
        this.getX = function() { return x; };
        this.setX = function(value) { x = value; };
        this.getY = function() { return y; };
        this.setY = function(value) { y = value; };
        this.getZ = function() { return z; };
        this.setZ = function(value) { z = value; };
        this.getName = function() { return name; };
        this.setName = function(value) { name = value; };
    }
    // Exported declarations
    return {Point: Point};
})();

var point1 = new points.Point(10, 20);

// "import"
var IPoint = points.Point;

var point2 = new IPoint(10, 20);
dumpObject("point1", point1);
dumpObject("point2", point2);

println("name is shared");
point1.setName("Changed name");
println("    point1.getName() = " + point1.getName());
println("    point2.getName() = " + point2.getName());

println("z is per-object");
point1.setZ(100);
point2.setZ(200);
println("    point1.getZ() = " + point1.getZ());
println("    point2.getZ() = " + point2.getZ());
