package com.example.demo.gof.b_structural.bridge.function;

import com.example.demo.gof.b_structural.bridge.implementaion.DisplayImpl;

public class DisplayOnPhone extends Display{
    public DisplayOnPhone(DisplayImpl displayImpl){
        super(displayImpl);
    }
    @Override
    public String displayOn(){
        return "Phone";
    }
}
