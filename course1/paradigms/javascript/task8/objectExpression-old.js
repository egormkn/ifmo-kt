/* HOMEWORK 9-10 */
"use strict";

var variables = ["x", "y", "z"];
var operators = {};

function operandFactory(evaluate) {
    var Operand = function(x){
        if(Variable && this instanceof Variable && variables.indexOf(x) == -1){
            throw new Error("Unknown variable: " + x);
        }
        this.value = x;
    };
    Operand.prototype = {
        evaluate: evaluate,
        toString: function() {
            return this.value.toString();
        },
        diff: function(x) {
            return num[this.value == x ? 1 : 0];
        },
        simplify: function(){
            return this;
        },
        prefix: toString
    };
    return Operand;
}

var Variable = operandFactory(function() {
    return arguments[variables.indexOf(this.value)];
});

var Const = operandFactory(function(){
    return Number(this.value);
});

var num = [new Const(0), new Const(1)];

function isConst(expr, value){
    return (expr instanceof Const && (value === undefined || expr.evaluate() == value));
}

function operatorFactory(arn, symbol, f) {
    var Operator = function(left, right){
        this.left = left;
        this.right = right;
    };
    Operator.prototype = {
        evaluate: function() {
            return f(this.left.evaluate.apply(this.left, arguments), this.right && this.right.evaluate.apply(this.right, arguments));
        },
        toString: function() {
            return this.left.toString() + " " + (arn == 2 ? this.right.toString() + " " : "") + symbol;
        },
        prefix: function(){
            return "(" + symbol + " " + this.left.prefix() + (arn == 2 ? " " + this.right.prefix() : "") + ")";
        },
        customSimplify: function(){
            return this;
        },
        simplify: function(){
            var left = this.left.simplify();
            var right = this.right && this.right.simplify();
            if(isConst(left) && (right === undefined || isConst(right))){
                return new Const(f(left.evaluate(), right && right.evaluate()));
            }
            return this.customSimplify(left, right);
        }
    };
    if(!operators[arn]){
        operators[arn] = {};
    }
    operators[arn][symbol] = Operator;
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

Add.prototype.diff = function(name){
    return new Add(this.left.diff(name), this.right.diff(name));
};

Add.prototype.customSimplify = function(left, right){
    if (isConst(left, 0)){
        return right;
    } else if (isConst(right, 0)){
        return left;
    } else {
        return new Add(left, right);
    }
};

Subtract.prototype.diff = function(name){
    return new Subtract(this.left.diff(name), this.right.diff(name));
};

Subtract.prototype.customSimplify = function(left, right){
    if (isConst(left, 0)){
        return new Negate(right);
    } else if (isConst(right, 0)){
        return left;
    } else {
        return new Subtract(left, right);
    }
};

Multiply.prototype.diff = function(name){
    return new Add(
        new Multiply(this.left.diff(name), this.right),
        new Multiply(this.left, this.right.diff(name))
    );
};

Multiply.prototype.customSimplify = function(left, right){
    if (isConst(left, 1)){
        return right;
    } else if (isConst(right, 1)){
        return left;
    } else if (isConst(left, 0) || isConst(right, 0)){
        return num[0];
    } else if (isConst(left, -1)){
        return new Negate(right);
    } else if (isConst(right, -1)){
        return new Negate(left);
    } else {
        return new Multiply(left, right);
    }
};

Divide.prototype.diff = function(name){
    return new Divide(
        new Subtract(
            new Multiply(this.left.diff(name), this.right), 
            new Multiply(this.left, this.right.diff(name))
        ), 
        new Multiply(this.right, this.right)
    );
};

Divide.prototype.customSimplify = function(left, right){
    if (isConst(left, 0)){
        return num[0];
    } else if (isConst(right, 1)){
        return left;
    } else if (isConst(right, -1)){
        return new Negate(left);
    }
    return new Divide(left, right);
};

Negate.prototype.diff = function(name){
    return new Negate(this.left.diff(name));
};

Negate.prototype.customSimplify = function(left, right){
    return new Negate(left);
};

Sin.prototype.diff = function(name){
    return new Multiply(new Cos(this.left), this.left.diff(name));
};

Cos.prototype.diff = function(name){
    return new Multiply(new Negate(new Sin(this.left)), this.left.diff(name));
};

var getTokens = function(str, regex) {
    var tokens = [];
    while (token = regex.exec(str)) {
        tokens.push({
            value: token[0],
            pos: token.index
        });
    }
    return tokens;
}

var parse = function(str){
    var a, b, 
        stack = [],
        input = getTokens(str, /\(|\)|[^\)\(\s]+/g);
    for (var i = 0; i < input.length; i++){
        if (input[i].value == ""){
            continue;
        }
        if (input[i].value in operators[1]){
            var a = stack.pop();
            stack.push(new operators[1][input[i]](a));
        } else if (input[i].value in operators[2]){
            var a = stack.pop();
            var b = stack.pop();
            stack.push(new operators[2][input[i]](b, a));
        } else if (variables.indexOf(input[i]) != -1){
            stack.push(new Variable(input[i]));
        } else if (/^[.\d]+$/.test(input[i])){
            stack.push(new Const(parseInt(input[i])));
        } else {
            throw new ParserError("Unexpected token: " + input[i]);
        }
    }
    return stack.pop();
};  

function ParserError(message) {  
    this.name = "ParserError";  
    this.message = message;  
}  
ParserError.prototype = Error.prototype;
 

var parsePrefix = function(str){
    var input = getTokens(str, regexp),
        pos = 0,
        level = 0;
    for (var i = 0; i < input.length; i++){
        var token = input[i];
        if (token.str in operators){
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


function median(){
    if(arguments.length == 0){
        throw new Error("No arguments for median");
    }
    var sum = 0;
    for(var i = 0; i < arguments.length; i++){
        sum += arguments[i];
    }
    return new Const(sum / arguments.length);
}

//println(median(1, 2, 3, 4, 5, 6, 7, 8, 9));