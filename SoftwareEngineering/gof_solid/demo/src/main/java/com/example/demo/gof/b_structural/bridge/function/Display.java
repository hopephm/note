package com.example.demo.gof.b_structural.bridge.function;

import com.example.demo.gof.b_structural.bridge.implementaion.DisplayImpl;

// 해당 객체가 Bridge
public abstract class Display {
    private DisplayImpl displayImpl;

    public Display(DisplayImpl displayImpl){
        this.displayImpl = displayImpl;
    }

    public String resolution(){
        return displayImpl.getResolution();
    }

    abstract public String displayOn();
}
