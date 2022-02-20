package com.example.demo.gof.c_behavioral.state;

public class Lamp {
    private LightState state;

    public Lamp(){
        this.state = OffState.getInstance();
    }

    public void click(){
        this.state = this.state.nextState();
    }

    public String getState(){
        return this.state.getState();
    }
}
