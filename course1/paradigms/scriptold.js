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
var negate = func(a => -a);

var cnst = function(value){
    return function(x){
        return value;
    }
};

var myb = function(arguments){
    for(j = 0; j < arguments.length; j++)
        println(arguments[j]);
};

var myf = function(){
    return myb(arguments);
};

myf("test1", "test2");
/*
var variable = function(name){
    return function(x){
        return name == "x" ? x : 0;
    };
};

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


var op = {
    "+": add,
    "-": subtract,
    "*": multiply,
    "/": divide
};

var parse = function(str){
    return function(x){
        stack = [];
        input = str.split(" ");
        for(var i = 0; i < input.length; i++){
            if("+/-*".indexOf(input[i]) == -1){
                var n = parseInt(input[i]);
                if(isNaN(n)){
                    stack.push(variable(input[i]));
                } else {
                    stack.push(cnst(n));
                }
            } else {
                var a = stack.pop();
                var b = stack.pop();
                stack.push(op[input[i]](b, a));
            }
        }
        
        
        return stack.pop()(x);
    }
};

println(parse("x x 2 - * x * 1 +")(5) + " == 76");*/