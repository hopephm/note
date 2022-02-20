package com.example.basic.repository;

import com.example.basic.domain.Person;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface PersonRepository extends JpaRepository<Person, Long> {
//    public List<String> findAllNames();
}
