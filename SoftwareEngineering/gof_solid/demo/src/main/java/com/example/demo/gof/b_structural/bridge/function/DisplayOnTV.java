package com.example.demo.gof.b_structural.bridge.function;

import com.example.demo.gof.b_structural.bridge.implementaion.DisplayImpl;

public class DisplayOnTV extends Display{
    public DisplayOnTV(DisplayImpl displayImpl){
        super(displayImpl);
    }
    @Override
    public String displayOn(){
        return "TV";
    }
}
