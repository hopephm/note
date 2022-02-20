package com.example.demo.gof.c_behavioral.state;

public class OnBlueState implements LightState {
    private static final LightState blueLight = new OnBlueState();
    public static LightState getInstance(){
        return blueLight;
    }

    @Override
    public LightState nextState(){
        return OffState.getInstance();
    }

    @Override
    public String getState() {
        return "BLUE";
    }
}
