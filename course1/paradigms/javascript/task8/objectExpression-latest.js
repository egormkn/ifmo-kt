/* HOMEWORK 9-10 */
"use strict";

/********************************* OPERANDS *********************************/

var variables = ["x", "y", "z"];

function operandFactory(evaluate) {
    var Operand = function(x){
        if(Variable && this instanceof Variable && variables.indexOf(x) == -1){
            throw new Error("Unknown variable: '" + x + "'");
        }
        this.value = x;
    };
    Operand.prototype = {
        evaluate: evaluate,
        toString: function() {
            return this.value.toString();
        },
        diff: function(x) {
            return num[this.value === x ? 1 : 0];
        },
        simplify: function(){
            return this;
        },
        prefix: toString
    };
    return Operand;
}

var Variable = operandFactory(function() {
    return Number(arguments[variables.indexOf(this.value)]);
});

var Const = operandFactory(function(){
    return Number(this.value);
});

var num = [new Const(0), new Const(1)];

function isConst(expr, value){
    return (expr instanceof Const && (value === undefined || expr.evaluate() == value));
}

Number.prototype.evaluate = function() {return this};
Number.prototype.diff = function() {return num[0]};
Number.prototype.simplify = Number.prototype.evaluate;
Number.prototype.prefix = Number.prototype.toString;

/********************************* OPERATORS *********************************/

var operators = {};

function asArray(a) {
    return Array.prototype.slice.call(a, 0);
}

function operatorFactory(arn, symbol, f) {
    var Operator = function(){
        if (arn != arguments.length) {
            throw new Error("Wrong number of arguments for '" + symbol + "'")
        }
        this.args = asArray(arguments);
        console.log(symbol + ": " + this.args.toString());
    };
    Operator.prototype = {
        evaluate: function() {
            var vars = asArray(arguments);
            return f.apply(this, this.args.map(function(arg){
                return arg.evaluate.apply(arg, vars);
            }));
        },
        toString: function() {
            return this.args.join(" ") + " " + symbol;
        },
        prefix: function(){
            return "(" + symbol + " " + this.args.join(" ") + ")";
        },
        customSimplify: function(){
            return this;
        },
        simplify: function(){
            var arr = this.args.map(function(x){
                return x.simplify();
            });
            if(arr.every(isConst)){
                return new Const(this.evaluate());
            }
            return this.customSimplify();
        }
    };
    operators[symbol] = {
        op: Operator,
        arn: arn
    };
    return Operator;
}

var Add      = operatorFactory(2, "+", function(a, b){return a + b;});
var Subtract = operatorFactory(2, "-", function(a, b){return a - b;});
var Multiply = operatorFactory(2, "*", function(a, b){return a * b;});
var Divide   = operatorFactory(2, "/", function(a, b){return a / b;});
var Sin      = operatorFactory(1, "sin", Math.sin);
var Cos      = operatorFactory(1, "cos", Math.cos);
var Abs      = operatorFactory(1, "abs", Math.abs);
var Log      = operatorFactory(1, "log", Math.log);
var Power    = operatorFactory(1, "**", Math.pow);
var Mod      = operatorFactory(1, "%", function(a, b){return a % b;});
var Negate   = operatorFactory(1, "negate", function(a){return -a;});
var Median15 = operatorFactory(15, "median15", function(){
    var values = asArray(arguments).sort(function (a, b) {return a - b});
    var half = Math.floor(values.length/2);
    if(values.length % 2) {
        return values[half];
    }
    return (values[half-1] + values[half]) / 2.0;
});

/***************************** CUSTOM PROTOTYPES *****************************/

Add.prototype.diff = function(name){
    return new Add(this.args[0].diff(name), this.args[1].diff(name));
};

Add.prototype.customSimplify = function(){
    if (isConst(this.args[0], 0)){
        return this.args[1];
    } else if (isConst(this.args[1], 0)){
        return this.args[0];
    } else {
        return new Add(this.args[0], this.args[1]);
    }
};

Subtract.prototype.diff = function(name){
    return new Subtract(this.args[0].diff(name), this.args[1].diff(name));
};

Subtract.prototype.customSimplify = function(){
    if (isConst(this.args[0], 0)){
        return new Negate(this.args[1]);
    } else if (isConst(this.args[1], 0)){
        return this.args[0];
    } else {
        return new Subtract(this.args[0], this.args[1]);
    }
};

Multiply.prototype.diff = function(name){
    return new Add(
        new Multiply(this.args[0].diff(name), this.args[1]),
        new Multiply(this.args[0], this.args[1].diff(name))
    );
};

Multiply.prototype.customSimplify = function(){
    if (isConst(this.args[0], 1)){
        return this.args[1];
    } else if (isConst(this.args[1], 1)){
        return this.args[0];
    } else if (isConst(this.args[0], 0) || isConst(this.args[1], 0)){
        return num[0];
    } else if (isConst(this.args[0], -1)){
        return new Negate(this.args[1]);
    } else if (isConst(this.args[1], -1)){
        return new Negate(this.args[0]);
    } else {
        return new Multiply(this.args[0], this.args[1]);
    }
};

Divide.prototype.diff = function(name){
    return new Divide(
        new Subtract(
            new Multiply(this.args[0].diff(name), this.args[1]), 
            new Multiply(this.args[0], this.args[1].diff(name))
        ), 
        new Multiply(this.args[1], this.args[1])
    );
};

Divide.prototype.customSimplify = function(){
    if (isConst(this.args[0], 0)){
        return num[0];
    } else if (isConst(this.args[1], 1)){
        return this.args[0];
    } else if (isConst(this.args[1], -1)){
        return new Negate(this.args[0]);
    }
    return new Divide(this.args[0], this.args[1]);
};

Negate.prototype.diff = function(name){
    return new Negate(this.args[0].diff(name));
};

Negate.prototype.customSimplify = function(){
    return new Negate(this.args[0]);
};

Sin.prototype.diff = function(name){
    return new Multiply(new Cos(this.args[0]), this.args[0].diff(name));
};

Cos.prototype.diff = function(name){
    return new Multiply(new Negate(new Sin(this.args[0])), this.args[0].diff(name));
};

/********************************** PARSERS **********************************/

function ParserError(message) {  
    this.name = "ParserError";  
    this.message = message;  
}  
ParserError.prototype = Error.prototype;

var parse = function(str){
    var a, b, 
        stack = [],
        input = str.split(" ");
    for (var i = 0; i < input.length; i++){
        if (input[i] == ""){
            continue;
        }
        if (input[i] in operators){
            var oper = operators[input[i]];
            var a = [];
            for(var i = 0; i < oper.arn; i++) {
                a[i] = stack.pop();
            }
            if (oper.arn == 1) {
                stack.push(new oper.op(a[0])); 
            } else {
                stack.push(new oper.op(a[1], a[0])); // FIXME
            }
        } else if (variables.indexOf(input[i]) != -1){
            stack.push(new Variable(input[i]));
        } else if (/^[.\d]+$/.test(input[i])){
            stack.push(new Const(parseFloat(input[i])));
        } else {
            throw new ParserError("Unexpected token: " + input[i]);
        }
    }
    return stack.pop();
};
    
var parsePrefix = function(str){
    var tokens = str.match(/\(|\)|[^\)\(\s]+/g);
    tokens.pos = 0;
    tokens.level = 0;
    tokens.next = function(){
        if (tokens.pos == tokens.length){
            throw new ParserError("Need more tokens");
        }
        return tokens[tokens.pos++];
    };
    if(tokens.length == 0){
        throw new ParserError("Empty string");
    }
    function getExpr(next){
        var token = next();
        if (token in operators[1]){
            var a = getExpr(next);
            return new operators[1][token](a);
        } else if (token in operators[2]){
            var a = getExpr(next);
            var b = getExpr(next);
            return new operators[2][token](a, b);
        } else if (variables.indexOf(token) != -1){
            return new Variable(token);
        } else if (/^\d+(\.\d+)?$/.test(token)){
            return new Const(parseInt(token));
        } else if (token == '('){
            tokens.level++;
            return getExpr(next);
        } else if (token == ')'){
            tokens.level--;
            if(tokens.level < 0){
                throw new ParserError("Parenthesis not opened");
            }
            return getExpr(next);
        } else {
            throw new ParserError("Unexpected token: " + token);
        }
    }
    if(token.level != 0){
        throw new ParserError("Parenthesis not closed");
    }
    return getExpr(tokens.next);
};
