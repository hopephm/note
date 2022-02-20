package com.example.demo.gof.a_creational.abstract_factory.factory;

import com.example.demo.gof.a_creational.abstract_factory.domain.Button;
import com.example.demo.gof.a_creational.abstract_factory.domain.MousePointer;

public interface PageFactory {
    public Button createButton();
    public MousePointer createMousePointer();
}
