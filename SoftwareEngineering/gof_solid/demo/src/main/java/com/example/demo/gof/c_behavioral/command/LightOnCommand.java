package com.example.demo.gof.c_behavioral.command;

public class LightOnCommand implements Command{
    Light light;
    public LightOnCommand(Light light){
        this.light = light;
    }

    @Override
    public String run(){
        return light.lightOn();
    }
}
