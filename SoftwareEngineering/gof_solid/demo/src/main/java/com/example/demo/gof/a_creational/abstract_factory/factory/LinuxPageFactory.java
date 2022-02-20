package com.example.demo.gof.a_creational.abstract_factory.factory;

import com.example.demo.gof.a_creational.abstract_factory.domain.Button;
import com.example.demo.gof.a_creational.abstract_factory.domain.LinuxButton;
import com.example.demo.gof.a_creational.abstract_factory.domain.LinuxMousePointer;
import com.example.demo.gof.a_creational.abstract_factory.domain.MousePointer;

public class LinuxPageFactory implements PageFactory{
    @Override
    public Button createButton(){
        return new LinuxButton();
    }
    @Override
    public MousePointer createMousePointer(){
        return new LinuxMousePointer();
    }
}
