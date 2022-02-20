package com.example.demo.gof.b_structural.decorator.decorator;

import com.example.demo.gof.b_structural.decorator.domain.Beverage;

public class MilkDecorator extends BeverageDecorator{
    public MilkDecorator(Beverage beverage){
        super(beverage);
    }
    @Override
    public int getCost(){
        return beverage.getCost() + 700;
    }
    @Override
    public String getDescription(){
        return beverage.getDescription() + " 우유추가";
    }

}
