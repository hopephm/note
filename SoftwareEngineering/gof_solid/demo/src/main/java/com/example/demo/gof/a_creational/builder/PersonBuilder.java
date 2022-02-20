package com.example.demo.gof.a_creational.builder;

public class PersonBuilder {
    private String name;
    private String age;

    public PersonBuilder name(String name){
        this.name = name;
        return this;
    }

    public PersonBuilder age(String age){
        this.age = age;
        return this;
    }

    public Person build(){
        Person person = new Person();
        person.setName(name);
        person.setAge(age);
        return person;
    }


}
