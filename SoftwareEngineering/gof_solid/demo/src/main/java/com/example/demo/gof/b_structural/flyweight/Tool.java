package com.example.demo.gof.b_structural.flyweight;

public class Tool {
    private String name;

    public Tool(String name){
        this.name = name;
    }

    public String getTool(){
        return this.name;
    }
}
