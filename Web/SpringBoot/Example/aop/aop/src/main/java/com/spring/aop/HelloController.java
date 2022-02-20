package com.spring.aop;

import com.spring.aop.aspects.PrintAfterMethod;
import com.spring.aop.domain.Domain1;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {
    @Autowired
    Domain1 domain1;

    @RequestMapping("/")
//    @CheckSomething(roles = {"role3"})
//    @CheckSomething
    public String index() {
        domain1.doNotThing();
        return "Greetings from Spring Boot!";
    }

    @RequestMapping("/throwException")
//    @CheckSomething(roles = {"role1", "role2"}
    @PrintAfterMethod
    public String throwAnException() throws Exception {
        throw new Exception("Hello from exception!");
    }
}