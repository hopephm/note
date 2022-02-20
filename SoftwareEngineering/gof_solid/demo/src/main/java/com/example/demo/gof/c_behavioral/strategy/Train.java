package com.example.demo.gof.c_behavioral.strategy;

public class Train implements Transportation{
    @Override
    public String move(){
        return "철로를 따라서";
    }
}
