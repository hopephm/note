package com.example.demo.gof.c_behavioral.command;

public class YoungerBrother {
    Command command;

    public void setCommand(Command command){
        this.command = command;
    }

    public String followOrder(){
        return command.run();
    }
}
