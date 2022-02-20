package com.example.demo.gof.c_behavioral.interpreter;

public class OlderBrotherInterpreter {
//    실제로는 적절한 문법에 대한 정의 및 해석에 대한 과정이 포함되어야 함
    public String interpret(String sentence){
        switch (sentence){
            case "물": return "가져와";
            case "불": return "좀 꺼줄래?";
            case "문": return "닫아라";
            default: return "꺼져";
        }
    }
}
