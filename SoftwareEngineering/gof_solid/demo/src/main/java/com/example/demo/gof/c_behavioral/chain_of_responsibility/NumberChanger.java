package com.example.demo.gof.c_behavioral.chain_of_responsibility;

public interface NumberChanger {
    public NumberChanger setNext(NumberChanger next);
    public int process(int num);
}
