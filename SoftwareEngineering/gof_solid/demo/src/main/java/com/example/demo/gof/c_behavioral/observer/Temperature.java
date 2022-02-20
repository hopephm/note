package com.example.demo.gof.c_behavioral.observer;

import java.util.ArrayList;
import java.util.List;

public class Temperature {
    private List<Observer> observers;
    private int temp;

    public Temperature(){
        this.observers = new ArrayList<>();
        this.temp = 0;
    }

    public void setTemp(int temp){
        this.temp = temp;
        this.notifyTemp();
    }

    public void registerObserver(Observer observer){
        observers.add(observer);
    }

    private void notifyTemp(){
        for(Observer observer: observers){
            observer.update(this.temp);
        }
    }
}
