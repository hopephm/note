package com.example.demo.gof.c_behavioral.observer;

public class CurrentTempDisplayer implements Observer{
    private int temp;

    public CurrentTempDisplayer(){
        this.temp = 0;
    }
    @Override
    public void update(int temp){
        this.temp = temp;
    }
    @Override
    public int display(){
        return this.temp;
    }
}
