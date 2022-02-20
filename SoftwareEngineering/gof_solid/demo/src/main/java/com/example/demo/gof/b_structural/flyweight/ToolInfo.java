package com.example.demo.gof.b_structural.flyweight;

public class ToolInfo {
    Tool tool;
    String info;

    public ToolInfo(Tool tool, String info){
        this.tool = tool;
        this.info = info;
    }

    public Tool getTool(){
        return this.tool;
    }

    public String getInfo(){
        return this.info;
    }
}
