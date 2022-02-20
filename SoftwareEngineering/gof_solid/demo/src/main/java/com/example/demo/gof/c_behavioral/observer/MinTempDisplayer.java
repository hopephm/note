package com.example.demo.gof.c_behavioral.observer;

public class MinTempDisplayer implements Observer{
    private int temp;

    public MinTempDisplayer(){
        this.temp = 0;
    }

    @Override
    public void update(int temp){
        if(this.temp == 0)
            this.temp = temp;
        else{
            if(temp < this.temp)
                this.temp = temp;
        }
    }
    @Override
    public int display(){
        return this.temp;
    }
}
