"use strict";

// Magic helper functions
function example(s, description) {
    var result;
    try {
        result = eval(s);
    } catch (e) {
        result = e;
    }
    if (description) {
        println(description + ":", s, "->", result);
    } else {
        println(s, "->", result);
    }
}

function examples(collection, template) {
    collection.forEach(function(name) { 
        return example(template.replace('#', name).replace('#', name));
    });
}

function section(name) {
    println();
    println("---", name, "---");
}

function chapter(name) {
    println();
    println("==========", name, "==========");
}

function lecture(name) {
    println();
    println("===================================");
    println("=== " + name);
    println("===================================");
}

// Helper function
function dumpObject(name, o) {
    println(name);
    for (var attribute in o) {
        if (typeof(o[attribute]) == "function") {
            println("    " + attribute + "() = " + o[attribute]());
        } else {
            println("    " + attribute + " = " + o[attribute]);
        }
    }
}

