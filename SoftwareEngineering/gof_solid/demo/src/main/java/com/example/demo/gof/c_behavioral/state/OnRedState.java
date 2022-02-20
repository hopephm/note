package com.example.demo.gof.c_behavioral.state;

public class OnRedState implements LightState {
    private static final LightState redLight = new OnRedState();
    public static LightState getInstance(){
        return redLight;
    }
    @Override
    public LightState nextState(){
        return OnGreenState.getInstance();
    }

    @Override
    public String getState() {
        return "RED";
    }
}
