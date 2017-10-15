"use strict";
////////////////////////////////////////////////
var inputfile  = process.argv[2] || "task1.in";
var outputfile = process.argv[3] || "task1.out";
var endOfLine  = "\r\n";
////////////////////////////////////////////////

console.time("Время выполнения");
var fs = require('fs');

var Node = function(key, args) {
    this.key = key;
    this.args = args;
    this.str = args === undefined ? key : 
        "(" + (args.length == 1 ? key : "") + args.map(arg => arg.str).join(key) + ")";
};

var Parser = function(expr) {
    this.expr = expr.replace(/[\t\r ]+/g, '');
    this.start = 0;
};

Parser.prototype = (function() {
    var getParser = function(operator, getLeft, getRight, binary) {
        return function() {
            this.check();
            var args = [], length = 0;
            args.push(this[getLeft]());
            while (this.start < this.expr.length && this.expr[this.start] == operator[length]) {
                this.start++;
                length++;
                if (length == operator.length) {
                    args.push(this[getRight]());
                    length = 0;
                    if (binary) {
                        break;
                    }
                }
            } 
            if (args.length > 1) {
                return new Node(operator, args);
            } else {
                return args[0];
            }
        };
    };
    return {
        check: function() {
            if (this.start >= this.expr.length) {
                throw new Error("Parser error");
            }
        },
        parseExpression: getParser("->", "parseDisjunction", "parseExpression", true),
        parseDisjunction: getParser("|", "parseConjunction", "parseConjunction"),
        parseConjunction: getParser("&", "parseNegation", "parseNegation"),
        parseNegation: function() {
            this.check();
            if (this.expr[this.start] == "!") {
                this.start++;
                return new Node("!", [this.parseNegation()]);
            } else if (this.expr[this.start] == "(") {
                this.start++;
                var expr = this.parseExpression();
                if (this.expr[this.start] == ")") {
                    this.start++;
                    return expr;
                } else {
                    throw new Error("Parser error");
                }
            } else if (/[A-Z]/.test(this.expr[this.start])) {
                var name = "";
                while (this.start < this.expr.length && /[A-Z0-9]/.test(this.expr[this.start])) {
                    name += this.expr[this.start++];
                }
                return new Node(name);
            } else {
                throw new Error("Parser error");
            }
        },
        parseHeader: function() {
            var header = this.expr.split("|-");
            if (header.length != 2) {
                throw new Error("Parser error");
            }
            var hypotheses = header[0].length == 0 ? [] : header[0].split(",");
            return {
                hypotheses: hypotheses.map(hypothesis => new Parser(hypothesis).parseExpression()),
                result: header[1]
            };
        }
    };
})();

var axioms = [
    "A->B->A",                     // 1
    "(A->B)->(A->B->C)->(A->C)",   // 2
    "A->B->A&B",                   // 3
    "A&B->A",                      // 4
    "A&B->B",                      // 5
    "A->A|B",                      // 6
    "B->A|B",                      // 7
    "(A->C)->(B->C)->(A|B->C)",    // 8
    "(A->B)->(A->!B)->!A",         // 9
    "!!A->A"                       // 10
].map(axiom => new Parser(axiom).parseExpression());

var data = fs.readFileSync(inputfile, 'utf-8').split(endOfLine);
data.pop(); // Removes empty string in the end of file

var header = new Parser(data[0]).parseHeader();

var expressions = [];
var proved = {};
var MP = {};

var compareTrees = function(expr, axiom, variables) {
    if (expr === undefined) {
        return false;
    }
    if (axiom.args === undefined) { // Axiom variable
        if (axiom.str in variables) {
            return variables[axiom.str].str == expr.str;
        } else {
            variables[axiom.str] = expr;
            return true;
        }
    } else if (axiom.key == expr.key && axiom.args.length <= expr.args.length) { // Axiom operator
        var res = true;
        for (var i = 0; i < axiom.args.length; i++) {
            res = res && compareTrees(expr.args[i], axiom.args[i], variables);
        }
        return res;
    }
    return false;
};

var count = 0;

var getAnnotation = function(index) {
    var expr = expressions[index];
    proved[expr.str] = index;
    if (expr.key == "->") {
        var toMP = MP[expr.args[1].str];
        var ins = {
            full: index,
            left: expr.args[0].str
        };
        if (toMP === undefined) {
            MP[expr.args[1].str] = [ins];
        } else {
            MP[expr.args[1].str].push(ins);
        }
    }
    for (var i = 0, array = axioms.concat(header.hypotheses); i < array.length; i++) {
        var variables = {};
        if (compareTrees(expr, array[i], variables)) {
            return (i < axioms.length ? "Сх. акс. " + (i+1) : "Предп. " + (i+1 - axioms.length));
        }
    }
    var inMP = MP[expr.str];
    if (inMP !== undefined) {
        for (var i = 0; i < inMP.length; i++) {
            var leftIndex = proved[inMP[i].left];
            if (leftIndex !== undefined) {
                return "M.P. " + (leftIndex + 1) + ", " + (inMP[i].full + 1);
            }
        }
    }  
    count++;
    return "Не доказано";
};

for(var i = 1; i < data.length; i++) {
    expressions[i-1] = new Parser(data[i]).parseExpression();
    data[i] = "(" + i + ") " + data[i] + " (" + getAnnotation(i-1) + ")";
}

fs.writeFileSync(outputfile, data.join(endOfLine) + endOfLine, 'utf-8');
console.timeEnd("Время выполнения");
console.log("Не доказано: " + count);