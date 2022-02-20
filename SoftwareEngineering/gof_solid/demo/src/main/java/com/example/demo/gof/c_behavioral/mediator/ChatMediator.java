package com.example.demo.gof.c_behavioral.mediator;

import java.util.ArrayList;
import java.util.List;

public class ChatMediator {
    private List<ChatUser> users;

    public ChatMediator(){
        users = new ArrayList<>();
    }

    public void join(ChatUser user){
        users.add(user);
    }

    public void sendMessage(Message message){
        for(ChatUser user: this.users){
            user.receive(message);
        }
    }
}
