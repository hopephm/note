package com.example.demo.gof.b_structural.composite;

public class Speaker extends ComputerDevice{
    public Speaker(String name, int price){
        super(name,price);
    }
    @Override
    public String function(){
        return "소리출력";
    }
}
