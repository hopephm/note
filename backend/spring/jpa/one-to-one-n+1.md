## 💬@OneToOne N+1 문제

---

### ⛱️ 핵심 요약
- @OneToOne을 통해 일대일 연관관계를 사용할 때는 foreign key가 있는 쪽에서 단방향으로 연결 후 별도 요청을 통해 조회하는 것이 N+1 문제를 피하는 데 효과적입니다.
- 양방향 연관관계를 사용해야 하고 항상 지연 로딩으로 가져오도록 하려면, 지연 상태 초기화 바이트코드 향상을 활성화해야 합니다.

---

### 📇 레퍼런스

```
Bidirectional @OneToOne lazy association
Although you might annotate the parent-side association to be fetched lazily, Hibernate cannot honor this request since it cannot know whether the association is null or not.

The only way to figure out whether there is an associated record on the child side is to fetch the child association using a secondary query. Because this can lead to N+1 query issues, it’s much more efficient to use unidirectional @OneToOne associations with the @MapsId annotation in place.

However, if you really need to use a bidirectional association and want to make sure that this is always going to be fetched lazily, then you need to enable lazy state initialization bytecode enhancement.
```
- JPA에서 양방향 `@OneToOne` 연관관계를 지연 로딩(lazy loading)으로 설정해도, Hibernate는 자식 엔티티가 존재하는지 여부를 알 수 없기 때문에 이를 준수할 수 없습니다.
  - java에서는 field access가 가능하기 때문에 fk로 존재여부를 모르는 상황에서 훅으로 호출 시점에 null일지, 엔티티를 갖는지 결정할 수 없음.
- 자식 엔티티가 존재하는지 확인하려면 보조 쿼리를 사용해야 하며, 이는 N+1 쿼리 문제를 초래할 수 있습니다
- 따라서, `@MapsId` 어노테이션을 사용하여 단방향 `@OneToOne` 연관관계를 사용하는 것이 훨씬 효율적입니다.
- 양방향 연관관계를 사용해야 하고 항상 지연 로딩으로 가져오도록 하려면, 지연 상태 초기화 바이트코드 향상을 활성화해야 합니다.

출처: https://docs.hibernate.org/orm/7.1/userguide/html_single/

---

### 🎯 바이트 코드 향상 활성화

```
plugins {
  id 'org.hibernate.orm' version 'x.x.x
}

hibernate {
  enhancement {
    lazyInitialization = true
    dirtyTracking = true
    associationManagement = true
    extendedEnhancement = false
  }
}
```
출처: https://github.com/hibernate/hibernate-orm/tree/main/tooling/hibernate-gradle-plugin
