package com.example.demo.gof.c_behavioral.command;

public class TurnOnTVCommand implements Command{
    TV tv;

    public TurnOnTVCommand(TV tv){
        this.tv = tv;
    }

    @Override
    public String run(){
        return tv.turnOn();
    }
}
