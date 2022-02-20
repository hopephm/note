package com.example.demo.gof;

import com.example.demo.gof.c_behavioral.chain_of_responsibility.NegativeNumberChanger;
import com.example.demo.gof.c_behavioral.chain_of_responsibility.NumberChanger;
import com.example.demo.gof.c_behavioral.chain_of_responsibility.PositiveNumberChanger;
import com.example.demo.gof.c_behavioral.chain_of_responsibility.ZeroNumberChanger;
import com.example.demo.gof.c_behavioral.command.*;
import com.example.demo.gof.c_behavioral.interpreter.OlderBrotherInterpreter;
import com.example.demo.gof.c_behavioral.mediator.ChatMediator;
import com.example.demo.gof.c_behavioral.mediator.ChatUser;
import com.example.demo.gof.c_behavioral.memento.Book;
import com.example.demo.gof.c_behavioral.memento.Bookmark;
import com.example.demo.gof.c_behavioral.memento.BookmarkInfo;
import com.example.demo.gof.c_behavioral.observer.*;
import com.example.demo.gof.c_behavioral.observer.Observer;
import com.example.demo.gof.c_behavioral.state.Lamp;
import com.example.demo.gof.c_behavioral.strategy.Airplane;
import com.example.demo.gof.c_behavioral.strategy.Car;
import com.example.demo.gof.c_behavioral.strategy.MoveStrategy;
import com.example.demo.gof.c_behavioral.strategy.Train;
import com.example.demo.gof.c_behavioral.template_method.AdderTemplate;
import com.example.demo.gof.c_behavioral.template_method.MultiplierTemplate;
import com.example.demo.gof.c_behavioral.template_method.Operator;
import com.example.demo.gof.c_behavioral.visitor.Father;
import com.example.demo.gof.c_behavioral.visitor.Greeting;
import com.example.demo.gof.c_behavioral.visitor.Mother;
import com.example.demo.gof.c_behavioral.visitor.YoungerSister;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.*;

@SpringBootTest
public class BehavioralTest {
    @Test
    public void chainOfResponsibilityTest(){
//        각 체인에서 처리가능하면 처리, 불가하면 다른 객체에 책임 전가

//        양수라면 *10, 음수라면 *100, 0이라면 +1 하는 체인
        NumberChanger chain = new PositiveNumberChanger().setNext(new NegativeNumberChanger().setNext(new ZeroNumberChanger()));

        MatcherAssert.assertThat(chain.process(1), Matchers.is(10));
        MatcherAssert.assertThat(chain.process(-1), Matchers.is(-100));
        MatcherAssert.assertThat(chain.process(0), Matchers.is(1));
    }

    @Test
    public void commandTest(){
//      Command에 따라 실행 객체의 명령 변화 없이 다른 동작 수행 (행위의 캡슐화)
        TV tv = new TV();
        Light light = new Light();

        Command tvCommand = new TurnOnTVCommand(tv);
        Command lightCommand = new LightOnCommand(light);

        YoungerBrother brother = new YoungerBrother();

        brother.setCommand(tvCommand);
        MatcherAssert.assertThat(brother.followOrder(), Matchers.is("TV 켰다.."));
        brother.setCommand(lightCommand);
        MatcherAssert.assertThat(brother.followOrder(), Matchers.is("불 켰다.. 그만 좀 시켜 ㅡㅡ"));
    }

    @Test
    public void interpreterTest(){
//        문법에 대해 문법 분석을 통해, 해석된 문장 도출 (꼭 언어적 문법이 아니라 오토마타 설계가 되는 것이면 모두 가능할 듯)
        OlderBrotherInterpreter interpreter = new OlderBrotherInterpreter();
        
        MatcherAssert.assertThat(interpreter.interpret("물"), Matchers.is("가져와"));
        MatcherAssert.assertThat(interpreter.interpret("불"), Matchers.is("좀 꺼줄래?"));
        MatcherAssert.assertThat(interpreter.interpret("문"), Matchers.is("닫아라"));
        MatcherAssert.assertThat(interpreter.interpret("ㅇㅋ"), Matchers.is("꺼져"));
        MatcherAssert.assertThat(interpreter.interpret("알았다"), Matchers.is("꺼져"));
        MatcherAssert.assertThat(interpreter.interpret("꺼져"), Matchers.is("꺼져"));
    }

    @Test
    public void iteratorTest(){
//        연속적 요소 접근 대행 객체
        List<Integer> numbers = new ArrayList<>();

        Iterator<Integer> it;

        for(int i = 0; i < 3; i++) {
            numbers.add(i+1);
        }

        int i = 1;
        it = numbers.iterator();
        while(it.hasNext()){
            MatcherAssert.assertThat(it.next(), Matchers.is(i++));
        }
    }

    @Test
    public void mediatorTest(){
//        각 채팅방 사용자가 다른 모든 사용자에게 전송하지만 관계는 mediator하고만 맺고 있음
        ChatMediator chatRoom = new ChatMediator();

        ChatUser user1 = new ChatUser(chatRoom,"형석");
        ChatUser user2 = new ChatUser(chatRoom,"종혁");
        ChatUser user3 = new ChatUser(chatRoom,"희망");

        chatRoom.join(user1);
        chatRoom.join(user2);
        chatRoom.join(user3);

        user1.send("안녕? 얘들아");
        user2.send("하위");
        user3.send("시끄럽구나");

        final String expectedContents = "형석:안녕? 얘들아\n" +
                "종혁:하위\n" +
                "희망:시끄럽구나\n";

        MatcherAssert.assertThat(user1.getReceivedMessage(), Matchers.is(expectedContents));
        MatcherAssert.assertThat(user2.getReceivedMessage(), Matchers.is(user3.getReceivedMessage()));
    }

    @Test
    public void mementoTest(){
//        각 상태 저장 및 필요시 호출, 복구
        Book book = new Book();
        Bookmark bookmark;
        BookmarkInfo bookmarkInfo = new BookmarkInfo();

        book.read();    // 실행마다 +10페이지
        bookmark = book.bookmarking();
        bookmarkInfo.add(bookmark);

        book.read();
        book.read();    // 30
        bookmark = book.bookmarking();
        bookmarkInfo.add(bookmark);

        book.read();    // 40
        bookmark = book.bookmarking();
        bookmarkInfo.add(bookmark);

        bookmark = bookmarkInfo.get(1);
        book.openPage(bookmark); // 30

        book.read();
        book.read(); // 50
        bookmark = book.bookmarking();
        bookmarkInfo.add(bookmark);

        MatcherAssert.assertThat(book.getCurrentPage(), Matchers.is(50));
        MatcherAssert.assertThat(bookmarkInfo.get(0).getPage(), Matchers.is(10));
        MatcherAssert.assertThat(bookmarkInfo.get(1).getPage(), Matchers.is(30));
        MatcherAssert.assertThat(bookmarkInfo.get(2).getPage(), Matchers.is(40));
        MatcherAssert.assertThat(bookmarkInfo.get(3).getPage(), Matchers.is(50));
    }

    @Test
    public void observerTest(){
        // 특정 객체의 상태변화를 Observer 객체들이 감지, 감지하여 각자의 기능 수행
        Temperature temperature = new Temperature();

        Observer currentTempDisplayer = new CurrentTempDisplayer();
        Observer maxTempDisplayer = new MaxTempDisplayer();
        Observer minTempDisplayer = new MinTempDisplayer();

        temperature.registerObserver(currentTempDisplayer);
        temperature.registerObserver(maxTempDisplayer);
        temperature.registerObserver(minTempDisplayer);

        temperature.setTemp(20);
        temperature.setTemp(31);
        temperature.setTemp(29);
        temperature.setTemp(7);
        temperature.setTemp(-1);
        temperature.setTemp(11);

        MatcherAssert.assertThat(currentTempDisplayer.display(), Matchers.is(11));
        MatcherAssert.assertThat(maxTempDisplayer.display(), Matchers.is(31));
        MatcherAssert.assertThat(minTempDisplayer.display(), Matchers.is(-1));
    }

    @Test
    public void stateTest(){
        // 어떤 객체의 상태를 상태 객체로 표현 (Enum의 유지보수 단점 보완)
        Lamp lamp = new Lamp();
        MatcherAssert.assertThat(lamp.getState(), Matchers.is("OFF"));

        lamp.click();
        MatcherAssert.assertThat(lamp.getState(), Matchers.is("RED"));
        lamp.click();
        MatcherAssert.assertThat(lamp.getState(), Matchers.is("GREEN"));
        lamp.click();
        MatcherAssert.assertThat(lamp.getState(), Matchers.is("BLUE"));
        lamp.click();
        MatcherAssert.assertThat(lamp.getState(), Matchers.is("OFF"));
    }

    @Test
    public void strategyTest(){
        // 어떤 방법, 객체, 해결에 대해 인터페이스를 두어 동적으로 동작을 달리하도록
        MoveStrategy moveStrategy = new MoveStrategy();

        Car car = new Car();
        Train train = new Train();
        Airplane airplane = new Airplane();

        moveStrategy.setTransportation(car);
        MatcherAssert.assertThat(moveStrategy.howToMove(), Matchers.is("도로를 따라서"));

        moveStrategy.setTransportation(train);
        MatcherAssert.assertThat(moveStrategy.howToMove(), Matchers.is("철로를 따라서"));

        moveStrategy.setTransportation(airplane);
        MatcherAssert.assertThat(moveStrategy.howToMove(), Matchers.is("하늘을 날아서"));
    }

    @Test
    public void templateMethodTest(){
//        핵심 로직(더할지, 곱할지)에만 차이를 두고 주변 로직 공통 사용
//        템플릿: 입력수에 10을 곱하고, 원하는 로직 수행 후, 결과 값을 integer로 출력

        Operator adderWithTemplate = new AdderTemplate();
        Operator multiplierWithTemplate = new MultiplierTemplate();


        MatcherAssert.assertThat(adderWithTemplate.operate(1.19f), Matchers.is(23));
        MatcherAssert.assertThat(multiplierWithTemplate.operate(1.19f), Matchers.is(141));
    }
    
    @Test
    public void vistorTest(){
//        방문하는 객체에 따라 같은 메소드에서 행동의 방식이 다름.
        Greeting hello = new Greeting();

        Father father = new Father();
        Mother mother = new Mother();
        YoungerSister sister = new YoungerSister();

        MatcherAssert.assertThat(hello.greet(father), Matchers.is("Zzz.."));
        MatcherAssert.assertThat(hello.greet(mother), Matchers.is("지금시간이몇시야"));
        MatcherAssert.assertThat(hello.greet(sister), Matchers.is("왔냐"));
    }
}
