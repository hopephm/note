package com.example.demo.gof.b_structural.proxy;

public class User {
    private String id;

    public User(String id){
        this.id = id;
    }

    public String getId(){
        return this.id;
    }
}
