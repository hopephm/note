# Redis Java 클라이언트 비교: Lettuce vs Redisson

Redis를 Java 환경에서 사용할 때 대표적인 클라이언트 라이브러리인 **Lettuce**와 **Redisson**을 비교하고, 상황별 적합성을 정리합니다.

---

## 1. 기본 개념

| 라이브러리 | 개념 |
|------------|------|
| Lettuce | Redis 공식 기반 Java 클라이언트. 비동기/반응형 API 지원. 단일 및 클러스터 Redis 모두 사용 가능. |
| Redisson | Redis 기반 분산 자료구조 및 고급 기능 제공 Java 클라이언트. RLock, 세마포어, 분산 컬렉션 등 제공. |

---

## 2. 주요 특징

| 항목 | Lettuce | Redisson |
|------|---------|----------|
| API | Sync / Async / Reactive 지원 | Sync / Async 지원 |
| 동시성 | Thread-safe, Netty 기반 논블로킹 I/O | Thread-safe, 동기/비동기 모두 가능 |
| 분산 락 | 직접 구현 필요 (SETNX + EXPIRE) | RLock 등 Redlock 기반 분산 락 제공 |
| 고급 자료구조 | 없음 | RMap, RQueue, RSet, ReadWriteLock, 세마포어 등 |
| TTL 관리 | 수동 | 자동 연장(Auto-renew) 지원 |
| 클러스터 지원 | 지원 (직접 관리 필요) | 지원, 분산 환경 안전하게 설계됨 |
| 설치/의존성 | 가벼움, Redis 서버 기본 기능만 사용 | 다소 무거움, 분산 락 및 고급 자료구조 사용 시 필요 |
| 목적 | Redis 명령어 실행, 간단 락, Pub/Sub, Streams | 분산 환경에서 안전한 락, 고급 자료구조, 복잡한 서버 측 연산 |

---

## 3. 락 구현 방식

| 항목 | Lettuce | Redisson |
|------|---------|----------|
| 구현 방법 | SETNX + EXPIRE, 직접 TTL 관리 | RLock.lock()/unlock(), Redlock 기반 분산 락 |
| 분산 안전성 | 단일 서버 환경에서만 안전 | Redlock 기반 분산 환경 안전 |
| 장점 | 간단, 가볍고 빠름 | 분산 환경에서도 안전, 자동 갱신, 다양한 락 타입 제공 |
| 단점 | 분산 환경에서는 안전하지 않음, TTL/재시도 직접 구현 필요 | 클러스터 환경 의존, 단일 노드에서는 불필요, 라이브러리 오버헤드 존재 |

---

## 4. 사용 환경별 적합성

| 환경 | 추천 라이브러리 | 이유 |
|------|----------------|------|
| 단일 Redis 노드, 단순 CRUD 및 캐시, 간단 락 | Lettuce | 가볍고 설정 필요 없음, 단순 작업에 충분 |
| 단일 Redis 노드 + 단순 Pub/Sub, Streams | Lettuce | 빠른 비동기/반응형 처리 가능 |
| 다중 Redis 노드 / Redis 클러스터 + 분산 락 필요 | Redisson | Redlock 기반 안전한 락 제공, TTL 자동 갱신, 분산 환경 최적 |
| 분산 환경에서 RMap, RQueue, 세마포어 등 고급 자료구조 필요 | Redisson | 클러스터 환경에서 안전하고 편리하게 사용 가능 |
| 단순 키-값 CRUD, 분산 락 필요 없음 | Lettuce | Redisson 기능 필요 없으므로 오버헤드 발생 |

---

## 5. 요약

- **Lettuce**
    - 가볍고 빠른 Redis 클라이언트
    - 단일 노드, 단순 락 및 데이터 구조 사용 시 적합
    - 클러스터 지원 가능하지만 분산 락은 직접 구현 필요

- **Redisson**
    - Redis 기반 분산 자료구조 & 락 제공
    - 분산 환경에서 락 안전성, TTL 자동 연장, 고급 자료구조 필요할 때 적합
    - 단일 노드에서는 대부분의 기능이 불필요, 라이브러리 오버헤드 존재

**결론:**  
- 단일 Redis 환경에서는 Lettuce를, 분산 Redis 환경에서 안정적인 락과 고급 자료구조를 활용해야 할 때 Redisson을 사용하는 것이 합리적
