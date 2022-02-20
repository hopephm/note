package com.example.demo.gof.b_structural.composite;

public abstract class ComputerDevice {
    private String name;
    private int price;

    public ComputerDevice(String name, int price){
        this.name = name;
        this.price = price;
    }

    public String getName(){
        return this.name;
    }

    public int getPrice(){
        return this.price;
    }
    public abstract String function();
}
