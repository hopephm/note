## 💬 Java Options 우선순위

---
### ☝️핵심 요약
1. java option은 같은 키에 대해 나중에 적용된 값으로 적용
2. java 명령행 > _JAVA_OPTIONS > JDK_JAVA_OPTIONS > JVM_TOOL_OPTIONS > JVM default 순서로 우선순위를 갖게 됨 (실제 적용 순서는 반대)

- 출처
  - https://docs.oracle.com/javase/8/docs/technotes/guides/troubleshoot/envvars002.html
  - https://docs.oracle.com/en/java/javase/21/docs/specs/man/java.html

---
### 🪧 Java Option 적용
1. **JVM_TOOL_OPTIONS**
   1. JVM이 시작될 때 자동으로 읽음
   2. 옵션을 가장 앞쪽에 삽입
   3. 이후에 오는 모든 옵션에 의해 덮어씌워질 수 있음
2. **JDK_JAVA_OPTIONS**
   1. java 런처가 명령행 옵션보다 먼저 삽입 
   2. Java 9부터 공식 지원 
   3. JAVA_TOOL_OPTIONS 뒤, 명령행 앞에 위치
3. **_JAVA_OPTIONS**
   1. HotSpot JVM 런처가 자동으로 인식
   2. 명령행 옵션 이전 단계에서 적용
   3. _비공식 옵션(레퍼런스 미존재)_
   4. _**Oracle에서만 지원**된다는 내용이 존재 ([stackoverflow](https://stackoverflow.com/questions/28327620/difference-between-java-options-java-tool-options-and-java-opts))_
      1. _IBM은 ibm jvm을 까봐야 알 듯, **IBM_JAVA_OPTIONS** 사용([공식문서](https://www.ibm.com/docs/ko/sdk-java-technology/8?topic=applications-specifying-java-options-system-properties))_ 
4. **java 명령행**
   1. 사용자가 직접 지정 
   2. 가장 마지막에 파싱
   3. 같은 키가 있으면 무조건 최종 값
   4. _보통 관례로 **JAVA_OPTIONS**를 명령행에서 적용_ 
