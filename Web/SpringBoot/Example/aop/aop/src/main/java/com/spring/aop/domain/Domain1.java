package com.spring.aop.domain;

import com.spring.aop.aspects.PrintAfterMethod;
import org.springframework.stereotype.Component;

@Component
public class Domain1 {
    @PrintAfterMethod
    public void doNotThing(){
    }
}
