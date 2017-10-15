"use strict";

lecture("Functions");
chapter("Types");
section("Variables are typeless");

var a = 1;
println("a ->", a);

a = "Hello";
println("a ->", a);

section("Values are typed");
var as = ["'Hello'", 1, 1.1, [1, 2, 3], new Array(1, 2, 3), null, undefined];
for (var i = 0; i < as.length; i++) {
    println("a =", as[i]);
    println("    typeof(a) ->", typeof(as[i]));
}

section("Ordinary comparison");
println("'1' == '1' ->", '1' == '1');
println("'1' == 1 ->", '1' == 1);
println("undefined == undefined ->", undefined == undefined);
println("undefined == null ->", undefined == null);
println("null == null ->", null == null);

section("Strict comparison");
println("'1' === '1' ->", '1' === '1');
println("'1' === 1 ->", '1' === 1);
println("undefined === undefined ->", undefined === undefined);
println("undefined === null ->", undefined === null);
println("null === null ->", null === null);

section("Calculations");
println("2 + 3 ->", 2 + 3);
println("2.1 + 3.1 ->", 2.1 + 3.1);
println("'2.1' + '3.1' ->", '2.1' + '3.1');

section("Arrays");
as = [10, 20, 30];
println("as ->", "[" + as +"]"); 
println("as[2] ->", as[2]);
println("as[3] ->", as[3]);
println('as["2"] ->', as["2"]);

section("Arrays are mutable");
as.push(40);
println("as.push(40) -> ", "[" + as + "]");
as.push(50);
println("as.unshift(50) ->", "[" + as + "]");
