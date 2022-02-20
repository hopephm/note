package com.example.demo.gof.c_behavioral.template_method;

public class AdderTemplate extends Operator{
    @Override
    protected float calculate(float a){
        return a+a;
    }
}
