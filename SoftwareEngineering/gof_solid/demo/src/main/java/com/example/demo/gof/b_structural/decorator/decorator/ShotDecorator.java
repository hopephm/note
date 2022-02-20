package com.example.demo.gof.b_structural.decorator.decorator;

import com.example.demo.gof.b_structural.decorator.domain.Beverage;

public class ShotDecorator extends BeverageDecorator{
    public ShotDecorator(Beverage beverage){
        super(beverage);
    }
    @Override
    public int getCost(){
        return beverage.getCost() + 500;
    }
    @Override
    public String getDescription(){
        return beverage.getDescription() + " 샷추가";
    }
}
