package com.example.demo.gof;

import com.example.demo.gof.a_creational.abstract_factory.domain.Button;
import com.example.demo.gof.a_creational.abstract_factory.domain.MousePointer;
import com.example.demo.gof.a_creational.abstract_factory.factory.LinuxPageFactory;
import com.example.demo.gof.a_creational.abstract_factory.factory.PageFactory;
import com.example.demo.gof.a_creational.abstract_factory.factory.WindowsPageFactory;
import com.example.demo.gof.a_creational.builder.Person;
import com.example.demo.gof.a_creational.factory_method.FactoryMethod;
import com.example.demo.gof.a_creational.factory_method.domain.Human;
import com.example.demo.gof.a_creational.prototype.Item;
import com.example.demo.gof.a_creational.singleton.Context;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;


// 문자열 바뀔 일 없는 애들은 복사해서 쓰자.. enum 말고..

@SpringBootTest
public class CreationalTest {
    @Test
    public void abstractFactoryTest(){
//        상황에 따라 여러 객체를 생성하는 팩토리 결정
        String OS = "LINUX";
        PageFactory pageFactory = null;
        if(OS == "WINDOWS") pageFactory = new WindowsPageFactory();
        else if(OS == "LINUX") pageFactory = new LinuxPageFactory();

        Button button = pageFactory.createButton();
        MousePointer mousePointer = pageFactory.createMousePointer();

        String btnRst = button.paint();
        String mpRst = mousePointer.paint();

        if(OS == "LINUX"){
            MatcherAssert.assertThat(btnRst, Matchers.is("Linux Button"));
            MatcherAssert.assertThat(mpRst, Matchers.is("Linux Mouse Pointer"));
        }

        if(OS == "WINDOWS"){
            MatcherAssert.assertThat(btnRst, Matchers.is("Windows Button"));
            MatcherAssert.assertThat(mpRst, Matchers.is("Windows Mouse Pointer"));
        }
    }

    @Test
    public void BuilderTest(){
//        빌더 객체를 통해, 생성자에 비해 유연한 생성
        Person person = Person.builder()
                .name("희망")
                .age("27")
                .build();

        MatcherAssert.assertThat(person.getName(), Matchers.is("희망"));
        MatcherAssert.assertThat(person.getAge(), Matchers.is("27"));
    }
    
    @Test
    public void factoryMethodTest(){
//        메소드의 인자에 따라 다른 객체 생성
        FactoryMethod factoryMethod = new FactoryMethod();
        Human human = factoryMethod.createHuman("남자");

        MatcherAssert.assertThat(human.sayHello(), Matchers.is("Hello, I'm a man"));
    }
    
    @Test
    public void prototypeTest(){
//        객체 생성시 이미 정의된 프로토 타입을 통해 복사하여 생성
        Item item = new Item("사과", "채소");

        Item item2 = (Item) item.clone();
        item2.setName("참외");

        Item item3 = (Item) item.clone();
        item3.setName("수박");

        MatcherAssert.assertThat(item.getName(), Matchers.is("사과"));
        MatcherAssert.assertThat(item2.getName(), Matchers.is("참외"));
        MatcherAssert.assertThat(item3.getName(), Matchers.is("수박"));
    }

    @Test
    public void singletonTest(){
//        시스템에 하나의 객체만을 사용
        Context context = Context.getContext();
        context.setState("처음상태");
        
        Context context2 = Context.getContext();
        context2.setState("바뀐상태");

        MatcherAssert.assertThat(context.getState(), Matchers.is("바뀐상태"));
        
    }
}
