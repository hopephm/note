package com.example.demo.gof.c_behavioral.chain_of_responsibility;

public class ZeroNumberChanger implements NumberChanger{
    private NumberChanger next;
    @Override
    public NumberChanger  setNext(NumberChanger next){
        this.next = next;
        return this;
    }
    @Override
    public int process(int num){
        return num+1;
    }
}
