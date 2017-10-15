var stack = [];

/*
var add = function(left, right){
    return function(x){
        return left(x) + right(x);
    };
};
*/

var binary = function(f){
    function(a, b){
        return function(x){
            return f(a(x), b(x));
        }
    }
};

var cnst = function(value){
    return function(x){
        return value;
    };
};

var variable = function(name){
    return function(x){
        return name == "x" ? x : 0;
    };
};

var add = binary((a, b) => a + b);
var subtract = binary((a, b) => a - b);
var multiply = binary((a, b) => a * b);
var divide = binary((a, b) => a / b);

var expr = subtract(
    multiply(
        cnst(2),
        variable("x")
    ),
    cnst(3)
);
println(expr(5));


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
    println(expr(i));
}