package com.example.demo.gof.b_structural.decorator.decorator;

import com.example.demo.gof.b_structural.decorator.domain.Beverage;

public abstract class BeverageDecorator implements Beverage{
    protected Beverage beverage;

    public BeverageDecorator(Beverage beverage){
        this.beverage = beverage;
    }
}
