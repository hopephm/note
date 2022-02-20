package com.example.demo.gof.a_creational.factory_method;

import com.example.demo.gof.a_creational.factory_method.domain.Human;
import com.example.demo.gof.a_creational.factory_method.domain.Man;
import com.example.demo.gof.a_creational.factory_method.domain.Woman;

public class FactoryMethod {
    public Human createHuman(String sex){
        Human human=null;
        switch (sex){
            case "남자": human = new Man(); break;
            case "여자": human = new Woman(); break;
        }
        return human;
    }
}
