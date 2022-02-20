package com.example.demo.gof.b_structural.decorator.domain;

public class CafeMoca implements Beverage{
    @Override
    public int getCost(){
        return 5100;
    }
    @Override
    public String getDescription(){
        return "카페모카";
    }
}

