"use strict";

var variables = ["x", "y", "z"];

var operators = {
    unary: {},
    binary: {}
};

/* BASIC */
var func = function(op, name, f){
    var operator = function(a, b){
        return function(x, y, z){
            return f(a(x, y, z), b && b(x, y, z));
        }
    };
    op[name] = operator;
    return operator;
};

var add = func(operators.binary, "+", function(a, b){return a + b;});
var subtract = func(operators.binary, "-", function(a, b){return a - b;});
var multiply = func(operators.binary, "*", function(a, b){return a * b;});
var divide = func(operators.binary, "/", function(a, b){return a / b;});

var cnst = function(value){
    return function(){
        return Number(value);
    }
};

var variable = function(name){
    return function(){
        return arguments[variables.indexOf(name)];
    };
};
/* BASIC */

/* EASY */
var abs = func(operators.unary, "abs", Math.abs);
var log = func(operators.unary, "log", Math.log);
var power = func(operators.unary, "**", Math.pow);
var mod = func(operators.unary, "%", function(a, b){return a % b;});
var negate = func(operators.unary, "negate", function(a){return -a;});
/* EASY */

/* HARD */
var parse = function(str){
    var stack = [];
    var input = str.split(" ");
    for (var i = 0; i < input.length; i++){
        if (input[i] == ""){
        } else if(input[i] in operators.unary){
            var a = stack.pop();
            stack.push(operators.unary[input[i]](a));
        } else if (input[i] in operators.binary){
            var a = stack.pop();
            var b = stack.pop();
            stack.push(operators.binary[input[i]](b, a));
        } else {
            stack.push(variables.indexOf(input[i]) != -1 ? variable(input[i]) : cnst(input[i]));
        }
    }
    var expr = stack.pop();
    return function(x, y, z){
        return expr(x, y, z);
    }
};
/* HARD */