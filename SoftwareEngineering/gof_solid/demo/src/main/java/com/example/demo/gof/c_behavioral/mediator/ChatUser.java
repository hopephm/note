package com.example.demo.gof.c_behavioral.mediator;

public class ChatUser {
    private ChatMediator mediator;

    private String name;
    private String receivedMsg;

    public ChatUser(ChatMediator mediator, String name){
        this.mediator = mediator;
        this.name = name;
        this.receivedMsg = "";
    }

    public String getName(){
        return this.name;
    }

    public String getReceivedMessage(){
        return this.receivedMsg;
    }

    public void send(String msg){
        mediator.sendMessage(new Message(this, msg));
    }

    public void receive(Message message){
        this.receivedMsg += message.getSender().getName()+":"+message.getMessage()+"\n";
    }

}
