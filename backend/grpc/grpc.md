## gRPC

---

### 1. 정의
gRPC는 **Google이 개발한 고성능 원격 프로시저 호출(Remote Procedure Call) 프레임워크**로, HTTP/2 기반과 Protocol Buffers 직렬화를 사용합니다.  
주 사용 사례: 마이크로서비스 간 통신, 실시간 스트리밍, 클라우드 API

---

### 2. 구조

1. **HTTP/2 기반**
    - **멀티플렉싱(Multiplexing)**: 하나의 TCP 연결에서 여러 요청과 응답을 동시에 처리 가능 → 연결 수 최소화, 동시성 향상
    - **헤더 압축(Header Compression)**: 요청/응답 헤더 크기 최소화 → 네트워크 효율 증가
    - **스트리밍 지원(Streaming)**: Server, Client, Bidirectional 스트리밍으로 양방향 실시간 데이터 전송 가능
      - Server Streaming: 클라이언트 1 → 서버 N 응답
      - Client Streaming: 클라이언트 N → 서버 1 응답
      - Bidirectional Streaming: 양방향 N↔N 실시간 통신

2. **Protocol Buffers**
    - 직렬화/역직렬화 비용이 낮고, 타입 안전
    - 메시지 구조를 컴파일 타임에 검증 가능

3. **Stub 기반 호출**
    - 클라이언트는 `stub.method(request)`처럼 로컬 함수 호출처럼 사용 가능
    - 내부에서는 HTTP/2 + Protobuf로 직렬화 후 전송

---


### 3. 장단점
[**장점**]
- 빠른 통신 속도 (HTTP/2 + Protobuf)
- 타입 안전, 멀티플렉싱, 스트리밍 지원
- 파일 전송, 실시간 메시징, 양방향 스트리밍 가능
- 커넥션 재사용으로 레이턴시 감소

[**단점 / 고려사항**]
- 브라우저 직접 호출 제한 → gRPC-Web 필요
- 메시지 크기 제한, Backpressure 관리 필요
- Protobuf 학습 필요, TLS/인증 설정 필요
- TCP 연결을 유지하기 때문에 쿠버네티스 환경에서 로드밸런싱을 위해 별도 설정 필요

---

### 6. REST(HTTP/1.1) 대비 특징

| 항목 | REST (HTTP/1.1) | gRPC (HTTP/2) |
|------|----------------|----------------|
| 연결 | 요청마다 TCP 생성, Keep-Alive 가능 | 단일 TCP 연결 재사용, 멀티플렉싱 |
| 데이터 직렬화 | JSON | Protobuf (작고 빠름, 타입 안전) |
| 스트리밍 | 어렵거나 WebSocket/SSE 필요 | Server/Client/Bidirectional 스트리밍 기본 지원 |
| 동시 요청 처리 | 순차적, 연결별 한 요청 | 멀티플렉싱으로 동일 연결에서 다중 스트림 처리 |
| 레이턴시 | 연결 설정, 헤더 오버헤드 큼 | 헤더 압축 + 연결 재사용으로 낮음 |
| 오류/재시도 | 클라이언트 로직 필요 | gRPC/HTTP2에서 Retry, Deadline, Flow 제어 가능 |
