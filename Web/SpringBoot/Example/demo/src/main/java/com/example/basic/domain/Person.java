package com.example.basic.domain;

import lombok.Builder;
import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;

import javax.persistence.*;


@Data
@Entity
@Table(name = "person")
@NoArgsConstructor
@Getter
public class Person {
    @Id
    @GeneratedValue
    @Column(name="id")
    private Long id;

    @Column(name="name")
    private String name;

    @Column(name="age")
    private String age;

    @Builder
    public Person(String name, String age){
        this.name = name;
        this.age = age;
    }
}
