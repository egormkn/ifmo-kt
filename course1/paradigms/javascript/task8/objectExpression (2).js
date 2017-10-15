/* HOMEWORK 9-10 */
"use strict";

/********************************* OPERANDS *********************************/

var variables = ["x", "y", "z"];

function operandFactory(evaluate) {
    var Operand = function(x) {
        if (Variable && this instanceof Variable && variables.indexOf(x) == -1) {
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
        simplify: function() {
            return this;
        },
        prefix: function() {
            return this.value.toString();
        }
    };
    return Operand;
}

var Variable = operandFactory(function() {
    return Number(arguments[variables.indexOf(this.value)]);
});

var Const = operandFactory(function() {
    return Number(this.value);
});

var num = [new Const(0), new Const(1)];

function isConst(expr, value) {
    return (expr instanceof Const && (value === undefined || expr.evaluate() == value));
}

/********************************* OPERATORS *********************************/

var operators = {};

function asArray(a) {
    return Array.prototype.slice.call(a, 0);
}

function operatorFactory(arn, symbol, f) {
    var Operator = function() {
        if (arn != arguments.length) {
            throw new Error("Wrong number of arguments for '" + symbol + "'")
        }
        this.args = asArray(arguments);
    };
    Operator.prototype = {
        evaluate: function() {
            var vars = asArray(arguments);
            return f.apply(this, this.args.map(function(arg) {
                return arg.evaluate.apply(arg, vars);
            }));
        },
        toString: function() {
            return this.args.join(" ") + " " + symbol;
        },
        prefix: function() {
            return "(" + symbol + " " + this.args.join(" ") + ")";
        },
        customSimplify: function(simplified) {
            return this;
        },
        simplify: function() {
            var simplified = this.args.map(function(x) {
                return x.simplify();
            });
            if (simplified.every(function(x) {
                    return isConst(x);
                })) {
                return new Const(f.apply(this, simplified.map(function(arg) {
                    return arg.evaluate();
                })));
            }
            return this.customSimplify(simplified);
        }
    };
    operators[symbol] = {
        op: Operator,
        arn: arn
    };
    return Operator;
}

var Add      = operatorFactory(2, "+", function(a, b) {return a + b;});
var Subtract = operatorFactory(2, "-", function(a, b) {return a - b;});
var Multiply = operatorFactory(2, "*", function(a, b) {return a * b;});
var Divide   = operatorFactory(2, "/", function(a, b) {return a / b;});
var Sin      = operatorFactory(1, "sin", Math.sin);
var Cos      = operatorFactory(1, "cos", Math.cos);
var Abs      = operatorFactory(1, "abs", Math.abs);
var Log      = operatorFactory(1, "log", Math.log);
var Power    = operatorFactory(1, "**", Math.pow);
var Mod      = operatorFactory(1, "%", function(a, b) {return a % b;});
var Negate   = operatorFactory(1, "negate", function(a) {return -a;});
var Median15 = operatorFactory(15, "median15", function() {
    var values = asArray(arguments).sort(function(a, b) {
        return a - b
    });
    var half = Math.floor(values.length / 2);
    if (values.length % 2) {
        return values[half];
    }
    return (values[half - 1] + values[half]) / 2;
});

/***************************** CUSTOM PROTOTYPES *****************************/

Add.prototype.diff = function(name) {
    return new Add(this.args[0].diff(name), this.args[1].diff(name));
};

Add.prototype.customSimplify = function(simplified) {
    if (isConst(simplified[0], 0)) {
        return simplified[1];
    } else if (isConst(simplified[1], 0)) {
        return simplified[0];
    } else {
        return new Add(simplified[0], simplified[1]);
    }
};

Subtract.prototype.diff = function(name) {
    return new Subtract(this.args[0].diff(name), this.args[1].diff(name));
};

Subtract.prototype.customSimplify = function(simplified) {
    if (isConst(simplified[0], 0)) {
        return new Negate(simplified[1]).simplify();
    } else if (isConst(simplified[1], 0)) {
        return simplified[0];
    } else {
        return new Subtract(simplified[0], simplified[1]);
    }
};

Multiply.prototype.diff = function(name) {
    return new Add(
        new Multiply(this.args[0].diff(name), this.args[1]),
        new Multiply(this.args[0], this.args[1].diff(name))
    );
};

Multiply.prototype.customSimplify = function(simplified) {
    if (isConst(simplified[0], 1)) {
        return simplified[1];
    } else if (isConst(simplified[1], 1)) {
        return simplified[0];
    } else if (isConst(simplified[0], 0) || isConst(simplified[1], 0)) {
        return num[0];
    } else if (isConst(simplified[0], -1)) {
        return new Subtract(num[0], simplified[1]);
    } else if (isConst(simplified[1], -1)) {
        return new Subtract(num[0], simplified[0]);
    } else {
        return new Multiply(simplified[0], simplified[1]);
    }
};

Divide.prototype.diff = function(name) {
    return new Divide(
        new Subtract(
            new Multiply(this.args[0].diff(name), this.args[1]),
            new Multiply(this.args[0], this.args[1].diff(name))
        ),
        new Multiply(this.args[1], this.args[1])
    );
};

Divide.prototype.customSimplify = function(simplified) {
    if (isConst(simplified[0], 0)) {
        return num[0];
    } else if (isConst(simplified[1], 1)) {
        return simplified[0];
    } else if (isConst(simplified[1], -1)) {
        return new Subtract(num[0], simplified[0]);
    }
    return new Divide(simplified[0], simplified[1]);
};

Negate.prototype.diff = function(name) {
    return new Negate(this.args[0].diff(name));
};

Negate.prototype.customSimplify = function(simplified) {
    return new Negate(simplified[0]);
};

Sin.prototype.diff = function(name) {
    return new Multiply(new Cos(this.args[0]), this.args[0].diff(name));
};

Cos.prototype.diff = function(name) {
    return new Multiply(new Negate(new Sin(this.args[0])), this.args[0].diff(name));
};

/********************************** PARSERS **********************************/

function ParserError(message) {
    this.name = "ParserError";
    this.message = message;
}
ParserError.prototype = Error.prototype;

var getTokens = function(str, regex) {
    var token, tokens = [];
    while (token = regex.exec(str)) {
        tokens.push({
            value: token[0],
            pos: token.index
        });
    }
    return tokens;
};

var regexp = /\(|\)|[^\)\(\s]+/g;

var parse = function(str) {
    regexp.lastIndex = 0;
    var a, b,
    input = getTokens(str, /\(|\)|[^\)\(\s]+/g),
    stack = [];
    for (var i = 0; i < input.length; i++){
        if (input[i].value == ""){
            continue;
        }

        if (input[i].value in operators) {
            var oper = operators[input[i].value];
            var a = [];
            for (var j = oper.arn - 1; j >= 0; j--) {
                a[j] = stack.pop();
            }
            if (oper.arn == 1) {
                stack.push(new oper.op(a[0]));
            } else {
                stack.push(new oper.op(a[1], a[0])); // FIXME
            }
        } else if (variables.indexOf(input[i].value) != -1) {
            stack.push(new Variable(input[i].value));
        } else if (/^[-\.\d]+$/.test(input[i].value)) {
            stack.push(new Const(parseInt(input[i].value)));
        } else {
            throw new ParserError("Unexpected token '" + input[i].value + "' on position " + input[i].pos);
        }
    }
    return stack.pop();
};

var parsePrefix = function(str){
    var tokens = getTokens(str, /\(|\)|[^\)\(\s]+/g);
    println(tokens[3].value);
    var parStack = [];
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
        if (token.value in operators) {
            var oper = operators[token.value];
            var a = [];
            for (var i = 0; i < oper.arn; i++) {
                a[i] = getExpr(next);
            }
            if (oper.arn == 1) {
                return new oper.op(a[0]);
            } else {
                return new oper.op(a[0], a[1]); // FIXME
            }
        } else if (variables.indexOf(token.value) != -1){
            return new Variable(token.value);
        } else if (/^\d+(\.\d+)?$/.test(token.value)){
            return new Const(parseInt(token.value));
        } else if (token.value == '('){
            parStack.push(token.pos);
            tokens.level++;
            return getExpr(next);
        } else if (token.value == ')'){
            println(')');
            tokens.level--;
            if(tokens.level < 0){
                throw new ParserError("Parenthesis not opened for symbol on position " + token.pos);
            }
            parStack.pop();
            return getExpr(next);
        } else {
            throw new ParserError("Unexpected token: '" + token.value + "' on position " + token.pos);
        }
    }
    var result = getExpr(tokens.next);
    if(tokens.pos != tokens.length) {
        new ParserError("Parenthesis not opened for symbol on position " + tokens.pop().pos);
    }
    if(tokens.level != 0){
        throw new ParserError("Parenthesis not closed for symbol on position " + parStack.pop());
    }
    return result;
};


println(parsePrefix("+ x 2)"));