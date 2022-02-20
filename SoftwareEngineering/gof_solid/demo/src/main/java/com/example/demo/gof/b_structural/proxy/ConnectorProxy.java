package com.example.demo.gof.b_structural.proxy;

public class ConnectorProxy{
    private Connector connector;

    public ConnectorProxy(Connector connector){
        this.connector = connector;
    }

    public String connect(User user){
        if(user.getId() == "admin")
            return connector.connect(user);
        else
            return "permission denied";
    }
}
