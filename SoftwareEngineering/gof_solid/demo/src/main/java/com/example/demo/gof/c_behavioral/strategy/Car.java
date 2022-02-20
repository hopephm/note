package com.example.demo.gof.c_behavioral.strategy;

public class Car implements Transportation{
    @Override
    public String move(){
        return "도로를 따라서";
    }
}
