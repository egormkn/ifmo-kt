"use strict";

chapter("Functions");
section("dump");
var dump = function() {
    for (var i = 0; i < arguments.length; i++) {
        println(arguments[i]);
    }
};
println("dump =", dump);
dump(1, 2, "hello", null, undefined);

section("sum");
var sum = function() {
    var result = 0;
    for (var i = 0; i < arguments.length; i++) {
        result += arguments[i];
    }
    return result;
};
println("sum =", sum);
example("sum(1, 2, 3)");

section("minimum");
var minimum = function() {
    var result = Infinity;
    for (var i = 0; i < arguments.length; i++) {
        if (result > arguments[i]) {
            result = arguments[i];
        }
    }
    return result;
};
println("minimum =", minimum);
example("minimum(1, -2, 3)");

section("Minimum by absolute value");
var minimumByAbs = function() {
    var result = Infinity;
    for (var i = 0; i < arguments.length; i++) {
        if (Math.abs(result) > Math.abs(arguments[i])) {
            result = arguments[i];
        }
    }
    return result;
};
println("minimumByAbs =", minimumByAbs);
example("minimumByAbs(1, -2, 3)");

section("Unify minimum and minimumByAbs");
var minimumBy = function(comparator) {
    return function() {
        var result = Infinity;
        for (var i = 0; i < arguments.length; i++) {
            if (comparator(result, arguments[i]) > 0) {
                result = arguments[i];
            }
        }
        return result;
    }
};
var comparator = function(f) {
    return function(a, b) {
        return f(a) - f(b);
    }
};
var identity = function(a) { return a; };

minimum = minimumBy(comparator(identity));
minimumByAbs = minimumBy(comparator(Math.abs));

println("minimumBy =", minimumBy);
println("comparator =", comparator);
println("identity =", identity);
example("minimum(1, -2, 3)");
example("minimumByAbs(1, -2, 3)");

section("Unify minimumBy and sum");
function foldLeft(f, zero) {
    return function() {
        var result = zero;
        for (var i = 0; i < arguments.length;  i++) {
            result = f(result, arguments[i]);
        }
        return result;
    }
}
function minBy(f){
    return function(a, b) {
        return f(a) < f(b) ? a : b;
    }
}

sum = foldLeft(function(a, b) { return a + b; }, 0);
var multiply = foldLeft(function(a, b) { return a * b; }, 1);
minimumByAbs = foldLeft(minBy(comparator(Math.abs)), Infinity);
example("sum(1, -2, 3)");
example("multiply(1, -2, 3)");
example("minimumByAbs(1, -2, 3)");

section("sumSquares and sumAbs");
function square(x) { return x * x; }
var sumSquares = foldLeft(function(a, b) { return a + square(b) }, 0);
var sumAbs = foldLeft(function(a, b) { return a + Math.abs(b) }, 0);
example("sumSquares(1, -2, 3)");
example("sumAbs(1, -2, 3)");

section("Unify sumSquares and sumAbs");
function map(f) {
    return function() {
        var result = [];
        for (var i = 0; i < arguments.length; i++) {
            result.push(f(arguments[i]));
        }
        return result;
    }
}
function compose(f, g) {
    return function() {
        return f.apply(null, g.apply(null, arguments));
    }
}
sumSquares = compose(sum, map(square));
sumAbs = compose(sum, map(Math.abs));
example("sumSquares(1, -2, 3)");
example("sumAbs(1, -2, 3)");

println("diff");
var diff = function(dx) {
    return function(f) {
        return function(x) {
            return (f(x + dx) - f(x)) / dx;
        }
    }
};

var dsin = diff(1e-6)(Math.sin);
for (var i = 0; i < 10; i++) {
    println(i + " " + Math.cos(i) + " " + dsin(i) + " " + Math.abs(Math.cos(i) - dsin(i)));
}

section("curry");
var curry = function(f) {
    return function(a) {
        return function(b) {
            return f(a, b);
        }
    }
};

var add = curry(function(a, b) { return a + b; });
var add10 = add(10);
println(add(10)(20));
println(add10(20));

section("mCurry");
var mCurry = function(f) {
    return function(a) {
        return function() {
            var newArguments = [a];
            for (var i = 0; i < arguments.length; i++) {
                newArguments.push(arguments[i]);
            }
            return f.apply(null, newArguments);
        }
    }
};

var sub = mCurry(function(a, b, c) { return a - b - c; });
var sub10 = sub(10);
println(sub(10)(20, 30));
println(sub10(20, 30));
