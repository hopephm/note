package com.example.demo.gof.b_structural.composite;

import java.util.ArrayList;
import java.util.List;

public class Computer {
    private List<ComputerDevice> components = new ArrayList<>();

    public void addComponent(ComputerDevice computerDevice){
        components.add(computerDevice);
    }

    public List<ComputerDevice> getComponents(){
        return this.components;
    }
}
