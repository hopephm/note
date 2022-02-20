package com.example.demo.gof.c_behavioral.state;

public interface LightState {
    public LightState nextState();
    public String getState();
}
