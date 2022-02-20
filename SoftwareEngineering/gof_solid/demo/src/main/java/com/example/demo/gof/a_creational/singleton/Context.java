package com.example.demo.gof.a_creational.singleton;

public class Context {
    private static Context context;
    private String state;

    public void setState(String state){
        this.state = state;
    }

    public String getState(){
        return this.state;
    }

    public static Context getContext() {
        if(context == null)
            context = new Context();
        return context;
    }

    public Context(){
    }
}
