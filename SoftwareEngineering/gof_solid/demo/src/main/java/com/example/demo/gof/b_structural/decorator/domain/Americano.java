package com.example.demo.gof.b_structural.decorator.domain;

public class Americano implements Beverage{
    @Override
    public int getCost(){
        return 4000;
    }
    @Override
    public String getDescription(){
        return "아메리카노";
    }
}
