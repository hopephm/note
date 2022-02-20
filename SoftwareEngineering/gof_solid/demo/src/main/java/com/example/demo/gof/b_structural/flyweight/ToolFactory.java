package com.example.demo.gof.b_structural.flyweight;

import java.util.HashMap;
import java.util.Map;

public class ToolFactory {
//    pool 개념
    Map toolBox;

    public ToolFactory(){
        toolBox = new HashMap();
    }

    public ToolInfo getTool(String toolName){
        Tool tool = (Tool) toolBox.get(toolName);
        String info;

        if(tool == null){
            tool = new Tool(toolName);
            toolBox.put(toolName, tool);
            info = "새로구입";
        }else{
            info = "이미 존재, 꺼내 씀";
        }

        return new ToolInfo(tool, info);
    }
}
