package com.example.demo.gof.c_behavioral.strategy;

public class Airplane implements Transportation{
    @Override
    public String move(){
        return "하늘을 날아서";
    }
}
