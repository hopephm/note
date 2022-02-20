package com.example.demo.gof.b_structural.composite;

public class Keyboard extends ComputerDevice{
    public Keyboard(String name, int price){
        super(name,price);
    }
    @Override
    public String function(){
        return "자판입력";
    }
}
