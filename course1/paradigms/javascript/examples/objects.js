"use strict";

lecture("Objects and methods");

chapter("Objects");

section("Objects as associative arrays");

var point = {};
point["x"] = 1;
point["y"] = 2;
dumpObject("initial point", point);

point.x = 10;
point.y = 20;
dumpObject("modified point", point);

point = {"x": 100, "z": 200};
dumpObject("point with default values", point);
println();

println("Undefined property: " + point.qqq + " === " + point['qqq']);
println();

var strangeObject = {
    "hello world": "zzz",
    1: "qqq"
};
strangeObject["1 2"] = false;
dumpObject("strangeObject", strangeObject);
example('strangeObject[1] === strangeObject["1"]', "keys are strings")
example('point["x"] === point.x', "shorthand syntax");
println();

section("Properties testing");
example("'x' in point", "    point has property 'x'")
example("'a' in point", "    point has property 'a'")
println();

section("Properties dumping");
for (var property in point) {
    println("    point['" + property + "'] = " + point[property]);
}

section("Inheritance");
point = {x: 10, y: 20};
var shiftedPoint = Object.create(point);
shiftedPoint.dx = 1;
shiftedPoint.dy = 2;

dumpObject("point", point);
dumpObject("shiftedPoint", shiftedPoint);
println();

println("point is prototype of shiftedPoint: " + (Object.getPrototypeOf(shiftedPoint) === point));
println();

shiftedPoint.dx = -1;
dumpObject("shiftedPoint with modified dx", shiftedPoint);
println();

shiftedPoint.x = 1;
dumpObject("shiftedPoint with modified x", shiftedPoint);
dumpObject("point remains intact", point);
println();

point.y = 1000;
dumpObject("point with modified y", point);
dumpObject("shiftedPoint with propagated y", shiftedPoint);
println();

point.x = 1000;
dumpObject("point with modified x", point);
dumpObject("shiftedPoint without propagated x", shiftedPoint);
println();

delete shiftedPoint.x;
dumpObject("shiftedPoint with deleted local x", shiftedPoint);
println();

section("Methods");

point = {
    x: 10, 
    y: 20, 
    getX: function() {return point.x; },
    getY: function() {return point.y; }
};
dumpObject("Functions in properties: point", point);
println("Result of call  to getX: " + point.getX());
println("Actual value of getX: " + point.getX);
println();

shiftedPoint = Object.create(point);
shiftedPoint.dx = 1;
shiftedPoint.dy = 2;
shiftedPoint.getX = function() {return shiftedPoint.x + shiftedPoint.dx; };
shiftedPoint.getY = function() {return shiftedPoint.y + shiftedPoint.dy; };
dumpObject("Functions in properties: shiftedPoint", shiftedPoint);
println();

println("Aliasing problem");
var point2 = point;
dumpObject("point2 references to the same object as point", point2);

point = {x: -1, y: -2};
dumpObject("point references new object", point);
dumpObject("point2 has correct x and y, but strange getX() and getY()", point2);
println("point2.getX takes value from point, not from point2: " + point2.getX);
println();

point = {
    x: 10, 
    y: 20, 
    getX: function() {return this.x; },
    getY: function() {return this.y; }
};
point2 = point;
point = {x: -1, y: -2};
println("'this' -- the object, method in called on");
dumpObject("point", point);
dumpObject("methods of point2 references correct object", point2);
println("dot-notations is shorthand for array-notation: " + point2.getX() + " === " + point2["getX"]());
println();

println("Specifying context object in apply: " + 
    point2.getX.apply(point, ["other arguments"]) + ", " +
    point2.getX.apply(point2, ["other arguments"])
);
println("Specifying context object in call: " + 
    point2.getX.call(point, "other arguments") + ", " +
    point2.getX.call(point2, "other arguments")
);

section("Constructors");

function pointFactory(x, y) {
    var point = {};
    point.x = x;
    point.y = y;
    point.getX = function() { return this.x; };
    point.getY = function() { return this.y; };
    return point;
}
dumpObject("point produced by factory", pointFactory(10, 20));
println();

function Point(x, y) {
//    var point = {};
    this.x = x;
    this.y = y;
    this.getX = function() { return this.x; };
    this.getY = function() { return this.y; };
//    return point;
}
dumpObject("point created by constructor", new Point(10, 20));
println("Constructor is ordinary function: " + (typeof Point) + "\n" + Point);
println();

function PointWithPrototype(x, y) {
    this.x = x;
    this.y = y;
}
PointWithPrototype.prototype.getX = function() { return this.x; };
PointWithPrototype.prototype.getY = function() { return this.y; };
dumpObject("PointWithPrototype.prototype", PointWithPrototype.prototype);
dumpObject("point created by constructor with prototype", new PointWithPrototype(10, 20));
println();

point = Object.create(PointWithPrototype.prototype);
PointWithPrototype.call(point, 1, 2);
dumpObject("PointWithPrototype created without new", point);

