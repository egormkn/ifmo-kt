function cnf(formula) {
    formula = formula.replace("~", "!");
    var variables = new Array(10);
    var total = 0;
    "abcdefghijklmnopqrstuvwxyz".split("").forEach(function (l) {
        if (formula.includes(l)) {
            variables[total++] = l;
        }
    });
    var result = "";
    var first = true;
    for (var number = 0; number < 1 << total; ++number) {
        var replaced = formula;
        for (var i = 1; i <= total; ++i) {
            var letter = variables[total - i];
            var powered = 1 << (i - 1);
            replaced = replaced.replace(new RegExp(letter, "g"), (number & powered) === powered ? 1 : 0);
        }
        if (eval(replaced) === 0) {
            var subresult = "(";
            for(var i = 0; i < total; ++i) {
                if(i !== 0) {
                    subresult += "|";
                }
                var letter = variables[i];
                var powered = 1 << (total - i - 1);
                subresult += (number & powered) === powered ? "~" + letter : letter;
            }
            subresult += ")";
            if (!first) {
                result += "&" + subresult;
            } else {
                result = subresult;
            }
            first = false;
        }
    }
    if(result === "")
        result = "1";
    console.log(result);
    return result;
}

cnf("(~x|y)&(~(~~y|z)|~x)")