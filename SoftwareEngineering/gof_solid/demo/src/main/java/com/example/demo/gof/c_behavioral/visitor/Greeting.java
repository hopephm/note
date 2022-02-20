package com.example.demo.gof.c_behavioral.visitor;

public class Greeting {
    public String greet(Father father){
        return "Zzz..";
    }
    public String greet(Mother mother){
        return "지금시간이몇시야";
    }
    public String greet(YoungerSister youngerSister){
        return "왔냐";
    }
}
