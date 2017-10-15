function Something(){
    for(var i = 0; i < arguments.length; i++){
        console.log(" " + arguments[i]);
    }
}
/*function createSomething(){
    return new Something.apply(null, arguments);
}*/
var createSomething = (function() {
    function F(args) {
        return Something.apply(this, args);
    }
    F.prototype = Something.prototype;

    return function() {
        return new F(arguments);
    }
})();
//var s = createSomething(1, 2); // 's' is an instance of Something


var a = new Something(1, 2);
var b = new Something(3, 2);
console.log(a === b);