package com.example.basic;

import com.example.basic.domain.Person;
import com.example.basic.repository.PersonRepository;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.List;

@SpringBootTest
public class RepositoryTests {
    @Autowired
    PersonRepository personRepository;

    @Test
    public void repositoryTest(){
        for(int i = 0; i < 10; i++){
            Person person = Person.
            personRepository.save(person);
        }

        personRepository.findAll();
    }

    @Test
    public void n1Queries(){
//        List<String> names = personRepository.findAllNames();
        List<Person> names = personRepository.findAll();
        MatcherAssert.assertThat(names.size(), Matchers.is(10));
    }

}
