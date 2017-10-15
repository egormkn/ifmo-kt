function lex(string) {
    var tokens = string.match(/\(|\)|\d+(\.\d+)?|\w+|[+*\/-]/g);
    return tokens.map(function(token) {
        return /^\d/.test(token) ? parseFloat(token) : token;
    });
}

function parse(tokens) {
    var nodes = [];
    tokens.shift();
    while (token = tokens.shift()) {
        if (token == "(") {
            tokens.unshift(token);
            nodes.push(parse(tokens));
        } else if (token == ")") {
            return nodes;
        } else {
            nodes.push(token);
        }
    }
}

function interpret(node) {
    if (Array.isArray(node)) {
        var fn = interpret(node[0]);
        var args = node.slice(1).map(interpret);
        return fn.apply(null, args);
    } else if (typeof node === "number") {
        return node;
    } else {
        return environment[node];
    }
}

function compile(node) {
    if (Array.isArray(node)) {
        var operator = node[0];
        var values = node.slice(1).map(compile);
        return "(" + values.join(operator) + ")";
    } else {
        return node;
    }
}

var reduce = Array.prototype.reduce;
var environment = {};
environment["+"] = function() { return reduce.call(arguments, function(a,n) { return a + n; }, 0); };
environment["*"] = function() { return reduce.call(arguments, function(a,n) { return a * n; }, 1); };
environment["-"] = function(a,b) { return a - b; };
environment["/"] = function(a,b) { return a / b; };

function run(code) {
    var tokens = lex(code);
    var ast = parse(tokens.slice());
    var compiled = compile(ast);
    var interpretedResult = interpret(ast);
    var compiledResult = eval(compiled);

    console.log("tokens =>", tokens);
    console.log("ast =>", ast);
    console.log("compiled =>", compiled);
    console.log("");
    console.log("interpret(parse(lex(code))) =>", interpretedResult);
    console.log("eval(compile(parse(lex(code)))) =>", compiledResult);
}

run("(+ 1 2 (* 3.1415 42) (- 3 4) (/ 5 6))");
