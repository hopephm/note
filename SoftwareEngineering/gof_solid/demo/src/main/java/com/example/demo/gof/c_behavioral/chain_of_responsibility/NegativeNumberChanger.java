package com.example.demo.gof.c_behavioral.chain_of_responsibility;

public class NegativeNumberChanger implements NumberChanger{
    private NumberChanger next;
    @Override
    public NumberChanger setNext(NumberChanger next){
        this.next = next;
        return this;
    }
    @Override
    public int process(int num){
        if(num < 0) return num*100;
        else return next.process(num);
    }
}
