## Kotlin Coroutine

---

### 1. 정의
Kotlin Coroutine은 **경량화된 비동기/동시성 프로그래밍을 위한 설계 패러다임**
- **스레드 기반이 아닌 논블로킹(non-blocking) 방식**으로 동시성을 구현
- 기존 스레드보다 훨씬 적은 메모리로 수천~수만 개의 코루틴 실행 가능
- 비동기 로직을 동기 코드처럼 **읽기 쉽게 작성**할 수 있음

---

### 2. 핵심 특징
- **Suspending Function**
    - `suspend` 키워드로 정의된 함수
    - 코루틴 내에서 호출 가능하며, **실행 중 일시 중단(suspension) 후 재개(resume)** 가능
    - **컴파일 시 바이트코드 변환**
        - suspend function은 JVM 바이트코드에서 **추가 Continuation 파라미터**를 받는 형태로 변환
        - 내부적으로 **상태 머신(state machine)** 이 만들어져 현재 위치를 저장
        - 함수 호출 시:
          ```kotlin
             suspend fun fetchData(): String
          ```
          → 바이트코드 변환 후:
          ```java
             Object fetchData(Continuation<? super String> continuation)
          ```
            - `Continuation` 객체는 **현재 상태, 로컬 변수, 재개 위치** 정보를 포함
            - 코루틴이 일시 중단되면 상태 정보는 `Continuation`에 저장되고, 스레드는 블로킹되지 않음
    - **재개 시 동작**
        - 코루틴 엔진이 `Continuation.resume(value)`를 호출하면, 상태 머신을 기반으로 이전 중단 지점부터 실행 재개
        - 스레드는 Dispatcher에 의해 결정된 스레드 풀에서 계속 실행 가능
          ```
          suspend fun fetchData(): String {
              delay(1000) // 1초 대기, 스레드 블로킹 없음
              return "data"
          }
          ```

- **Coroutine Builder**
    - 코루틴을 시작하는 함수
    - 주요 빌더:
        - `launch` : 결과를 반환하지 않고 백그라운드 실행
        - `async` : 결과를 반환하고, `await()`로 결과 받을 수 있음
- **Coroutine Scope**
    - 코루틴 실행 범위 정의
    - `GlobalScope`, `CoroutineScope`, `lifecycleScope` 등 존재
    - 코루틴 취소(Cancellation)와 수명 관리 가능
- **Dispatcher**
    - 코루틴이 실행될 스레드 결정
    - 주요 디스패처와 역할:
        - `Dispatchers.Default` : CPU 연산 중심, 여러 코어 활용 → 연산 작업에 최적
        - `Dispatchers.IO` : 블로킹 I/O 중심, 스레드 풀 확장 가능 → 파일/네트워크 처리에 최적
        - `Dispatchers.Main` : UI 스레드 실행 → Android UI 업데이트나 메인 스레드 작업에 최적

---

### 3. 동시성 및 병렬성
- **Structured Concurrency**
    - 코루틴의 계층 구조를 통해 부모 코루틴이 취소되면 자식 코루틴도 자동 취소
- **Concurrency vs Parallelism**
    - `launch`/`async`를 통해 동시성(concurrency) 구현 가능
    - CPU 연산이 많은 경우 Dispatcher를 적절히 사용하면 병렬(parallel) 처리 가능

---

### 4. 장점
- **가독성**: 비동기 코드를 동기 코드처럼 작성 가능
- **경량화**: 스레드보다 메모리/오버헤드가 적음
- **취소/타임아웃 관리 용이**: `withTimeout`, `cancel()` 등 제공
- **통합 에코시스템**: Flow, Channel 등과 함께 reactive 패턴 구현 가능

---

### 5. 예제
```
fun main() = runBlocking {
    val job = launch(Dispatchers.Default) {
        repeat(5) { i ->
            println("Coroutine $i running on ${Thread.currentThread().name}")
            delay(500)
        }
    }
    job.join() // 완료 대기
```

---

### 6. 연관 개념
- **Flow**: 데이터 스트림을 코루틴 기반으로 처리, 비동기 시퀀스 제공
- **Channel**: 코루틴 간 메시지 전달/통신
- **Suspension Point**
    - 코루틴이 중단 가능한 지점
    - JVM 스레드를 블로킹하지 않고 `Continuation`에 상태를 저장
    - 재개 시 코루틴 엔진이 Dispatcher 위에서 상태 머신을 기반으로 다시 실행
