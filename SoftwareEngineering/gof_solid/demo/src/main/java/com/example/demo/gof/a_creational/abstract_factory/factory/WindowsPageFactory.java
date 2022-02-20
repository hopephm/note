package com.example.demo.gof.a_creational.abstract_factory.factory;

import com.example.demo.gof.a_creational.abstract_factory.domain.Button;
import com.example.demo.gof.a_creational.abstract_factory.domain.MousePointer;
import com.example.demo.gof.a_creational.abstract_factory.domain.WindowsButton;
import com.example.demo.gof.a_creational.abstract_factory.domain.WindowsMousePointer;

public class WindowsPageFactory implements PageFactory {
    @Override
    public Button createButton(){
        return new WindowsButton();
    }
    @Override
    public MousePointer createMousePointer(){
        return new WindowsMousePointer();
    }
}
