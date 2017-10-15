/* BASIC */
var func = function(f){
    return function(a, b){
        return function(x){
            return (b === undefined) ? f(a(x)) : f(a(x), b(x));
        }
    }
};

var add = func((a, b) => a + b);
var subtract = func((a, b) => a - b);
var multiply = func((a, b) => a * b);
var divide = func((a, b) => a / b);

var cnst = function(value){
    return function(x){
        return Number(value);
    }
};

var variable = function(name){
    return function(x){
        return name == "x" ? x : 0;
    };
};
/* BASIC */

/* EASY */
var abs = func(Math.abs);
var log = func(Math.log);
/* EASY */

/* HARD */
var op = {
    unary: {
        "abs": abs,
        "log": log
    },
    binary: {
        "+": add,
        "-": subtract,
        "*": multiply,
        "/": divide,
    }
};

var parse = function(str){
    return function(x){
        stack = [];
        input = str.split(" ");
        for(var i = 0; i < input.length; i++){
            if(input[i] in op.unary){
                var a = stack.pop();
                stack.push(op.unary[input[i]](a));
            } else if (input[i] in op.binary){
                var a = stack.pop();
                var b = stack.pop();
                stack.push(op.binary[input[i]](b, a));
            } else {
                stack.push(isNaN(parseInt(input[i])) ? variable(input[i]) : cnst(input[i]));
            }
        }
        return stack.pop()(x);
    }
};
/* HARD */

/* TESTS
var expr = subtract(
    multiply(
        cnst(2),
        variable("x")
    ),
    cnst(3)
);
println(expr(5) + " == " + 7);

expr = add(
    subtract(
        multiply(
            variable("x"),
            variable("x")
        ),
        multiply(
            cnst(2),
            variable("x")
        )
    ),
    cnst(1)
);

for(i = 0; i <= 10; i++){
    println(expr(i) + " == " + (i - 1) * (i - 1));
}

println(abs(cnst(-5))(0) + " == 5");
println(log(cnst(5))(0) + " == 1.6...");

println(parse("x x 2 - * x * 1 + -5 abs + 5 log +")(5) + " == 82.6....");
println(parse("5 log")(5) + " == 1.6");

TESTS */