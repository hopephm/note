package com.example.demo.gof.c_behavioral.state;

public class OnGreenState implements LightState {
    private static final LightState greenLight = new OnGreenState();
    public static LightState getInstance(){
        return greenLight;
    }

    @Override
    public LightState nextState(){
        return OnBlueState.getInstance();
    }

    @Override
    public String getState() {
        return "GREEN";
    }
}
