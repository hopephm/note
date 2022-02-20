package com.example.demo.gof.a_creational.prototype;

public class Item implements Cloneable{
    private String name;
    private String category;

    public Item(String name, String category){
        this.category = category;
        this.name = name;
    }

    public void setName(String name){
        this.name = name;
    }

    public void setCategory(String category){
        this.category = category;
    }

    public String getName(){
        return this.name;
    }

    public String getCategory(){
        return this.category;
    }

    @Override
    public Object clone(){
        Object clone = null;
        try{
            clone = super.clone();
        }catch (CloneNotSupportedException e){
            e.printStackTrace();
        }
        return clone;
    }
}
