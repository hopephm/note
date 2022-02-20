package com.example.demo.gof.b_structural.adapter;

public class Adapter220Vto110V {
    public Power110V convert(Power220V power220V){
        Power110V power110V = new Power110V();

        int power = power220V.getPower();
        power110V.setPower(power/2);

        return power110V;
    }
}
