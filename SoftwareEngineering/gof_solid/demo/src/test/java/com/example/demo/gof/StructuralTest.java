package com.example.demo.gof;

import com.example.demo.gof.b_structural.adapter.Adapter220Vto110V;
import com.example.demo.gof.b_structural.adapter.Power110V;
import com.example.demo.gof.b_structural.adapter.Power220V;
import com.example.demo.gof.b_structural.adapter.PowerSocket110V;
import com.example.demo.gof.b_structural.bridge.function.Display;
import com.example.demo.gof.b_structural.bridge.function.DisplayOnTV;
import com.example.demo.gof.b_structural.bridge.function.DisplayOnPhone;
import com.example.demo.gof.b_structural.bridge.implementaion.DisplayImpl2000;
import com.example.demo.gof.b_structural.bridge.implementaion.DisplayImpl2020;
import com.example.demo.gof.b_structural.composite.Computer;
import com.example.demo.gof.b_structural.composite.ComputerDevice;
import com.example.demo.gof.b_structural.composite.Keyboard;
import com.example.demo.gof.b_structural.composite.Speaker;
import com.example.demo.gof.b_structural.decorator.decorator.MilkDecorator;
import com.example.demo.gof.b_structural.decorator.decorator.ShotDecorator;
import com.example.demo.gof.b_structural.decorator.domain.Americano;
import com.example.demo.gof.b_structural.decorator.domain.Beverage;
import com.example.demo.gof.b_structural.decorator.domain.CafeMoca;
import com.example.demo.gof.b_structural.facade.EnvFacade;
import com.example.demo.gof.b_structural.flyweight.ToolFactory;
import com.example.demo.gof.b_structural.flyweight.ToolInfo;
import com.example.demo.gof.b_structural.proxy.Connector;
import com.example.demo.gof.b_structural.proxy.ConnectorProxy;
import com.example.demo.gof.b_structural.proxy.User;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.List;

// 문자열 바뀔 일 없는 애들은 복사해서 쓰자.. enum 말고..

@SpringBootTest
public class StructuralTest {
    @Test
    public void adapterTest(){
//        인터페이스가 다른 클래스의 인터페이스를 맞춰줌
        Power220V power220V = new Power220V();
        power220V.setPower(220);

        Adapter220Vto110V adapter = new Adapter220Vto110V();
        Power110V power110V = adapter.convert(power220V);

        PowerSocket110V powerSocket110V = new PowerSocket110V();
        String rst = powerSocket110V.plugIn(power110V);

        MatcherAssert.assertThat(rst, Matchers.is("Connected"));
    }

    @Test
    public void BridgeTest(){
        // 기능의 분리, Display가 Bridge
        Display displayOnTVIn2000 = new DisplayOnTV(new DisplayImpl2000());
        Display displayOnPhoneIn2020 = new DisplayOnPhone(new DisplayImpl2020());

        MatcherAssert.assertThat(displayOnTVIn2000.resolution(), Matchers.is("640 x 360"));
        MatcherAssert.assertThat(displayOnTVIn2000.displayOn(), Matchers.is("TV"));
        MatcherAssert.assertThat(displayOnPhoneIn2020.resolution(), Matchers.is("5120 x 2160"));
        MatcherAssert.assertThat(displayOnPhoneIn2020.displayOn(), Matchers.is("Phone"));
    }

    @Test
    public void compositeTest(){
//        각기 다른 구성요소 객체를 일반화하여 하나로 취급
        Computer computer = new Computer();
        ComputerDevice speaker = new Speaker("스피커", 2000);
        ComputerDevice keyboard = new Keyboard("키보드", 1000);

        computer.addComponent(speaker);
        computer.addComponent(keyboard);

        List<ComputerDevice> components = computer.getComponents();

        ComputerDevice component1 = components.get(0);
        ComputerDevice component2 = components.get(1);

        MatcherAssert.assertThat(component1,Matchers.is(speaker));
        MatcherAssert.assertThat(component2,Matchers.is(keyboard));
    }
    
    @Test
    public void decoratorTest(){
        // 어떤 기본 객체에 대해 그때그때 기능 동적 추가
        Beverage americanoAdd1ShotAnd2Milk = new ShotDecorator(new MilkDecorator(new MilkDecorator(new Americano())));
        Beverage cafemocaAdd1ShotAnd1Milk = new ShotDecorator(new MilkDecorator((new CafeMoca())));
        
        MatcherAssert.assertThat(americanoAdd1ShotAnd2Milk.getCost(), Matchers.is(5900));
        MatcherAssert.assertThat(americanoAdd1ShotAnd2Milk.getDescription(), Matchers.is("아메리카노 우유추가 우유추가 샷추가"));

        MatcherAssert.assertThat(cafemocaAdd1ShotAnd1Milk.getCost(), Matchers.is(6300));
        MatcherAssert.assertThat(cafemocaAdd1ShotAnd1Milk.getDescription(), Matchers.is("카페모카 우유추가 샷추가"));
    }

    @Test
    public void facadeTest(){
//        클라이언트 측에 드러나서 동작해야 하는 일을 묶음, 클라이언트는 서브시스템과 분리 : 그래서 구조 패턴 임
        EnvFacade envFacade = new EnvFacade();

//        동작이 OS, Version외의 다른 환경 setting이 필요해도 클라이언트측 코드는 바뀔 일이 없음
        envFacade.init();
        envFacade.setEnv();
    }

    @Test
    public void flyWeightTest(){
//        팩토리에 풀 형태로 같은 값을 갖는 객체 저장, 필요시 꺼내 씀
        ToolFactory toolFactory = new ToolFactory();

        ToolInfo ti1 = toolFactory.getTool("망치");
        ToolInfo ti2 = toolFactory.getTool("스패너");
        ToolInfo ti3 = toolFactory.getTool("드라이버");
        ToolInfo ti4 = toolFactory.getTool("망치");
        ToolInfo ti5 = toolFactory.getTool("드라이버");

        MatcherAssert.assertThat(ti1.getInfo(),Matchers.is("새로구입"));
        MatcherAssert.assertThat(ti2.getInfo(),Matchers.is("새로구입"));
        MatcherAssert.assertThat(ti3.getInfo(),Matchers.is("새로구입"));
        MatcherAssert.assertThat(ti4.getInfo(),Matchers.is("이미 존재, 꺼내 씀"));
        MatcherAssert.assertThat(ti5.getInfo(),Matchers.is("이미 존재, 꺼내 씀"));

        MatcherAssert.assertThat(ti1.getTool(),Matchers.is(ti4.getTool()));
        MatcherAssert.assertThat(ti3.getTool(),Matchers.is(ti5.getTool()));
    }

    @Test
    public void proxyTest(){
//        접근하고자 하는 객체에 하나의 계층을 추가하여 동작 (핵심로직 이외의 부가로직 추가)
        User normUser = new User("normal_user");
        User admin = new User("admin");

        Connector connector = new Connector();
        ConnectorProxy proxyConnector = new ConnectorProxy(connector);

        MatcherAssert.assertThat(connector.connect(normUser), Matchers.is("connected"));
        MatcherAssert.assertThat(connector.connect(admin), Matchers.is("connected"));
        MatcherAssert.assertThat(proxyConnector.connect(normUser), Matchers.is("permission denied"));
        MatcherAssert.assertThat(proxyConnector.connect(admin), Matchers.is("connected"));
    }
}
