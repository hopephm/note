package com.example.demo.gof.c_behavioral.mediator;

public class Message {
    ChatUser sender;
    String msg;

    public Message(ChatUser sender, String msg){
        this.sender = sender;
        this.msg = msg;
    }

    public String getMessage(){
        return this.msg;
    }

    public ChatUser getSender(){
        return this.sender;
    }

}
