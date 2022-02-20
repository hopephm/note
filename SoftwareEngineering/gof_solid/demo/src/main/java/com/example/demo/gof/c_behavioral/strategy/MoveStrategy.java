package com.example.demo.gof.c_behavioral.strategy;

public class MoveStrategy {
    private Transportation transportation;
    public void setTransportation(Transportation transportation){
        this.transportation = transportation;
    }

    public String howToMove(){
        return transportation.move();
    }
}
