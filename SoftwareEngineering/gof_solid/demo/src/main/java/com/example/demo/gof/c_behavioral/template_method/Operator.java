package com.example.demo.gof.c_behavioral.template_method;

public abstract class Operator {
    public int operate(float a) {
        a *= 10;
        a = calculate(a);
        return (int)a;
    }
    abstract protected float calculate(float b);
}
