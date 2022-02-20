package com.example.demo.gof.a_creational.builder;

public class Person {
    public static PersonBuilder builder(){
        return new PersonBuilder();
    }

    private String name;
    private String age;

    public void setName(String name){
        this.name = name;
    }

    public void setAge(String age){
        this.age = age;
    }

    public String getName(){
        return this.name;
    }
    public String getAge(){
        return this.age;
    }
}
