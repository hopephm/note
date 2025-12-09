## 💬 Spring ApplicationContext Initialization 과정

---

### ⛱️ 핵심 요약
1. **ApplicationContext 생성 및 refresh() 진입**
    - SpringApplication.run(): ApplicationContext 구현체 생성 후 refresh() 호출
    - AbstractApplicationContext.refresh(): Spring 컨테이너 전체 초기화 라이프사이클의 시작점
    - [*The ApplicationContext*](https://docs.spring.io/spring-framework/reference/core/beans/context-introduction.html), [*AbstractApplicationContext Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/support/AbstractApplicationContext.html)

2. **BeanFactory 생성 및 기본 환경 준비**
    - AbstractApplicationContext.prepareRefresh(): Environment 활성화, PropertySource 준비
    - AbstractApplicationContext.obtainFreshBeanFactory(): DefaultListableBeanFactory 생성 또는 초기화
    - AbstractApplicationContext.prepareBeanFactory(): ClassLoader 설정, Aware 인터페이스 처리기 등록, 기본 Scope 등록
    - [*AbstractApplicationContext Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/support/AbstractApplicationContext.html)

3. **BeanDefinitionRegistryPostProcessor 실행 (Configuration 처리의 시작점)**
    - PostProcessorRegistrationDelegate.invokeBeanFactoryPostProcessors(): BeanDefinitionRegistryPostProcessor 우선 실행
    - ConfigurationClassPostProcessor.postProcessBeanDefinitionRegistry(): @Configuration 해석의 공식 진입점
    - [*ConfigurationClassPostProcessor Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/annotation/ConfigurationClassPostProcessor.html)

4. **@Configuration 클래스 파싱**
    - ConfigurationClassParser.parse(): @ComponentScan, @Import, @PropertySource, @Bean 메타데이터 분석
    - [*Java-based Container Configuration*](https://docs.spring.io/spring-framework/reference/core/beans/java.html)

5. **컴포넌트 스캔을 통한 BeanDefinition 등록**
    - ClassPathBeanDefinitionScanner.scan(): @Component, @Service, @Repository, @Controller, 스캔 결과를 BeanDefinition으로 등록
    - [*ClassPathBeanDefinitionScanner Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/annotation/ClassPathBeanDefinitionScanner.html)

6. **@Import 처리 (설정 클래스 동적 확장)**
    - ImportSelector.selectImports(): Import 대상 클래스 목록 동적 반환
    - ImportBeanDefinitionRegistrar.registerBeanDefinitions(): 코드 기반 BeanDefinition 직접 등록
    - [*Composing Java-based Configurations*](https://docs.spring.io/spring-framework/reference/core/beans/java/composing-configuration-classes.html)

7. **@Bean 메서드를 BeanDefinition으로 변환**
    - ConfigurationClassBeanDefinitionReader.loadBeanDefinitions(): @Bean 메서드 하나당 BeanDefinition 생성, Factory Method 기반 BeanDefinition 등록
    - [*ConfigurationClassBeanDefinitionReader Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/annotation/ConfigurationClassBeanDefinitionReader.html)

8. **BeanFactoryPostProcessor 실행 (BeanDefinition 구조 최종 보정)**
    - PostProcessorRegistrationDelegate.invokeBeanFactoryPostProcessors(): PropertySourcesPlaceholderConfigurer, Custom BeanFactoryPostProcessor 등 실행
    - [*Container Extension Points*](https://docs.spring.io/spring-framework/reference/core/beans/factory-extension.html)

9. **BeanPostProcessor 등록 (Bean 생성 개입자 준비)**
    - PostProcessorRegistrationDelegate.registerBeanPostProcessors(): AutowiredAnnotationBeanPostProcessor, CommonAnnotationBeanPostProcessor, AbstractAutoProxyCreator
    - [*BeanPostProcessor*](https://docs.spring.io/spring-framework/reference/core/beans/factory-extension.html#beans-factory-extension-bpp)

10. **모든 Singleton Bean 인스턴스화 시작**
    - DefaultListableBeanFactory.preInstantiateSingletons(): lazy가 아닌 모든 singleton Bean 인스턴스화 트리거
    - [*DefaultListableBeanFactory Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/factory/support/DefaultListableBeanFactory.html)

11. **Bean 인스턴스 생성**
    - AbstractAutowireCapableBeanFactory.createBean(): 생성자 또는 팩토리 메서드 기반 인스턴스 생성
    - [*AbstractAutowireCapableBeanFactory Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/factory/support/AbstractAutowireCapableBeanFactory.html)

12. **의존성 주입**
    - AbstractAutowireCapableBeanFactory.populateBean(): @Autowired, @Value, @Qualifier 처리
    - [*Dependencies and Configuration in Detail*](https://docs.spring.io/spring-framework/reference/core/beans/dependencies.html)

13. **초기화 전 BeanPostProcessor 실행**
    - BeanPostProcessor.postProcessBeforeInitialization()
    - [*BeanPostProcessor Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/beans/factory/config/BeanPostProcessor.html)

14. **초기화 콜백 실행**
    - @PostConstruct, InitializingBean.afterPropertiesSet(), init-method
    - [*Initialization Callbacks*](https://docs.spring.io/spring-framework/reference/core/beans/factory-nature.html)

15. **초기화 후 BeanPostProcessor 실행 및 AOP Proxy 적용**
    - AbstractAutoProxyCreator.postProcessAfterInitialization(): Advisor 매칭, 프록시 대상 Bean이면 Proxy로 교체
    - [*AbstractAutoProxyCreator Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/aop/framework/autoproxy/AbstractAutoProxyCreator.html)

16. **ApplicationContext refresh 완료**
    - AbstractApplicationContext.finishRefresh(): ContextRefreshedEvent 발행, SmartLifecycle.start() 호출
    - [*AbstractApplicationContext Javadoc*](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/context/support/AbstractApplicationContext.html)
