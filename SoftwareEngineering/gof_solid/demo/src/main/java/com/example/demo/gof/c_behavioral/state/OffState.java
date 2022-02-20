package com.example.demo.gof.c_behavioral.state;

public class OffState implements LightState {
    private static final LightState off = new OffState();
    public static LightState getInstance(){
        return off;
    }
    @Override
    public LightState nextState(){
        return OnRedState.getInstance();
    }

    @Override
    public String getState() {
        return "OFF";
    }
}
