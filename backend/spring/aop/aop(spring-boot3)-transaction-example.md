## 💬Spring AOP 동작 과정

---

### ☝️핵심 요약
1. 대상이 interface인 경우, JDK Dynamic Proxy로 프록시 생성 (인터페이스 구현체로 대체)
2. 대상이 class인 경우, CGLIB Proxy로 프록시 생성 (클래스 상속 후 구현체 대체)
3. 둘 다 proxy로 동작하기 때문에 내부 호출에는 프록시가 적용되지 않음
    - 컴파일 시점에 이미 프록시 내부 함수를 호출하도록 되어 있기 때문에 런타임 시점에 프록시를 생성한다고 해도 대체하지 않음
4. 프록시 내부에서는 advisor 가 체인으로 등록되어 동작함 

---

### ⛱️ AOP 동작 요약 (feat. Transaction) 

**아래와 같은 과정으로 트랜잭션 처리**

1. TransactionAutoConfiguration
    - spring boot auto configuration으로 트랜잭션 관련 빈 등록
2. @EnableTransactionManagement
    - 트랜잭션 관련 구성 활성화 (TransactionManagementConfigurationSelector)
3. TransactionManagementConfigurationSelector
    - 트랜잭션 관련 구성을 선택 (AutoProxyRegistrar, ProxyTransactionManagementConfiguration)
4. ProxyTransactionManagementConfiguration
    - 트랜잭션 관련 빈 등록 (TransactionAttributeSource, TransactionInterceptor)
5. BeanFactoryTransactionAttributeSourceAdvisor
    - 트랜잭션 대상(PointCut, TransactionAttributeSource)과 트랜잭션 처리(Advice, TransactionInterceptor) 연결하고 AOP 처리 대상이되는 핵심
6. AutoProxyRegistrar
    - Aop 프록시 생성 빈 등록 (InfrastructureAdvisorAutoProxyCreator)
7. InfrastructureAdvisorAutoProxyCreator
    - Advisor(BeanFactoryTransactionAttributeSourceAdvisor)기반으로 프록시를 생성
8. TransactionInterceptor.invoke() / TransactionAspectSupport.invokeWithinTransaction()
   - 트랜잭션 대상 판단 > 트랜잭션 매니저 선택 > 트랜잭션 참여 여부 결정 > 비즈니스 로직 실행 > 예외 시 롤백, 동작 시 커밋
   - ThreadLocal에 트랜잭션 정보 저장하여 동작

---

### 🏛️ Spring Transaction 주요 클래스 구현부 및 동작
**spring boot 3.5.8 기준 (spring 6.2.14)**

1. **TransactionAutoConfiguration**
- **AbstractTransactionManagementConfiguration**로 트랜잭션 관련 구성을 설정하지 않은 경우, @EnableTransactionManagement 활성화
- spring.aop.proxy-target-class 프로퍼티에 따라 JDK Dynamic Proxy 또는 CGLIB 프록시 사용 설정
- 트랜잭션 매니저가 **PlatformTransactionManager**일 때 관련 빈 **TransactionTemplate** 등록
- 트랜잭션 매니저가 **ReactiveTransactionManager**일 때 관련 빈 **TransactionalOperator** 등록
- 트랜잭션 AOP 관련 빈이 존재할 때, **LazyInitializationExcludeFilter** 빈 등록

```java
@Configuration(proxyBeanMethods = false)
@ConditionalOnBean(TransactionManager.class)
@ConditionalOnMissingBean(AbstractTransactionManagementConfiguration.class)
public static class EnableTransactionManagementConfiguration {

    @Configuration(proxyBeanMethods = false)
    @EnableTransactionManagement(proxyTargetClass = false)
    @ConditionalOnBooleanProperty(name = "spring.aop.proxy-target-class", havingValue = false)
    public static class JdkDynamicAutoProxyConfiguration {

    }

    @Configuration(proxyBeanMethods = false)
    @EnableTransactionManagement(proxyTargetClass = true)
    @ConditionalOnBooleanProperty(name = "spring.aop.proxy-target-class", matchIfMissing = true)
    public static class CglibAutoProxyConfiguration {

    }

}
```

```java

@Configuration(proxyBeanMethods = false)
@ConditionalOnSingleCandidate(PlatformTransactionManager.class)
public static class TransactionTemplateConfiguration {

    @Bean
    @ConditionalOnMissingBean(TransactionOperations.class)
    public TransactionTemplate transactionTemplate(PlatformTransactionManager transactionManager) {
        return new TransactionTemplate(transactionManager);
    }

}
```

```java
@Bean
@ConditionalOnMissingBean
@ConditionalOnSingleCandidate(ReactiveTransactionManager.class)
public TransactionalOperator transactionalOperator(ReactiveTransactionManager transactionManager) {
    return TransactionalOperator.create(transactionManager);
}
```

```java
@Configuration(proxyBeanMethods = false)
@ConditionalOnBean(AbstractTransactionAspect.class)
static class AspectJTransactionManagementConfiguration {

    @Bean
    static LazyInitializationExcludeFilter eagerTransactionAspect() {
        return LazyInitializationExcludeFilter.forBeanTypes(AbstractTransactionAspect.class);
    }

}
```

---

2. **@EnableTransactionManagement**
- **TransactionManagementConfigurationSelector** 구성 포함
    - @Import는 지정된 클래스를 스프링 컨텍스트에 등록
- 각 속성 설명
    - proxyTargetClass: CGLIB 프록시 사용 여부 (기본값: false - JDK Dynamic Proxy 사용)
    - mode: AOP 적용 방식
        - PROXY: 프록시 방식, 기본 값
        - ASPECTJ: 컴파일 타임 위빙
    - order: AOP 프록시의 적용 순서 지정
        - LOWEST_PRECEDENCE: 가장 낮은 우선순위, 기본 값 (Integer.MIN_VALUE)
    - rollbackOn: 트랜잭션 롤백 조건 지정
        - RUNTIME_EXCEPTIONS: 런타임 예외 발생 시 롤백, 기본 값
        - ALL_EXCEPTIONS: 모든 예외 발생 시 롤백
```java
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Import(TransactionManagementConfigurationSelector.class)
public @interface EnableTransactionManagement {
	boolean proxyTargetClass() default false;
    
	AdviceMode mode() default AdviceMode.PROXY;
    
	int order() default Ordered.LOWEST_PRECEDENCE;
    
	RollbackOn rollbackOn() default RollbackOn.RUNTIME_EXCEPTIONS;
}
```

---
3. **TransactionManagementConfigurationSelector**
- AdviceMode에 따라 트랜잭션 관련 구성 선택
    - PROXY: **AutoProxyRegistrar**, **ProxyTransactionManagementConfiguration** 구성 포함
    - ASPECTJ: JTA 트랜잭션 또는 일반 트랜잭션 AOP 구성 포함


```java
public class TransactionManagementConfigurationSelector extends AdviceModeImportSelector<EnableTransactionManagement> {
	@Override
	protected String[] selectImports(AdviceMode adviceMode) {
		return switch (adviceMode) {
			case PROXY -> new String[] {AutoProxyRegistrar.class.getName(),
					ProxyTransactionManagementConfiguration.class.getName()};
			case ASPECTJ -> new String[] {determineTransactionAspectClass()};
		};
	}

	private String determineTransactionAspectClass() {
		return (ClassUtils.isPresent("jakarta.transaction.Transactional", getClass().getClassLoader()) ?
				TransactionManagementConfigUtils.JTA_TRANSACTION_ASPECT_CONFIGURATION_CLASS_NAME :
				TransactionManagementConfigUtils.TRANSACTION_ASPECT_CONFIGURATION_CLASS_NAME);
	}
}
```
- ⚠️ **TransactionManagementConfigurationSelector** : **AdviceModeImportSelector** : **ImportSelector**
    - **ImportSelector** 인터페이스 구현체들은 **ConfigurationClassParser**에서 처리되어 스프링 컨텍스트에 등록될 클래스 이름 배열을 반환

---
4. **ProxyTransactionManagementConfiguration**
- 트랜잭션 대상, 동작, 연결 빈 등록
    1. **TransactionAttributeSource** 빈 등록: 트랜잭션 대상 결정
        - **SpringTransactionAnnotationParser에서 org.springframework.transaction.annotation.Transactional 어노테이션이 붙은 클래스 위주 처리**
        - 상속한 **AbstractTransactionManagementConfiguration**에서 등록됨
        - jakarta.transaction.Transactional, jakarta.ejb.TransactionAttribute 지원
    2. **TransactionInterceptor** 빈 등록: 트랜잭션 처리 로직 구현
        - 등록된 **TransactionAttributeSource**기반으로 설정됨
    3. **BeanFactoryTransactionAttributeSourceAdvisor** 빈 등록: 트랜잭션 대상(pointCut)과 트랜잭션 처리(advice) 연결
        - 위에서 생성한 **TransactionInterceptor**와 **TransactionAttributeSource** 기반
        - 기본 구성에서 **TransactionInterceptor** 생성시, 이미 연결해주고 있음: 해당 빈 커스텀을 통해, 트랜잭션 AOP 동작 변경 가능
        - **InfrastructureAdvisorAutoProxyCreator**에 의해 advisor로 스캔되어 프록시 생성에 활용되는 핵심 클래스

```java
@Configuration(proxyBeanMethods = false)
@Role(BeanDefinition.ROLE_INFRASTRUCTURE)
@ImportRuntimeHints(TransactionRuntimeHints.class)
public class ProxyTransactionManagementConfiguration extends AbstractTransactionManagementConfiguration {

	@Bean(name = TransactionManagementConfigUtils.TRANSACTION_ADVISOR_BEAN_NAME)
	@Role(BeanDefinition.ROLE_INFRASTRUCTURE)
	public BeanFactoryTransactionAttributeSourceAdvisor transactionAdvisor(
			TransactionAttributeSource transactionAttributeSource, TransactionInterceptor transactionInterceptor) {

		BeanFactoryTransactionAttributeSourceAdvisor advisor = new BeanFactoryTransactionAttributeSourceAdvisor();
		advisor.setTransactionAttributeSource(transactionAttributeSource);
		advisor.setAdvice(transactionInterceptor);
		if (this.enableTx != null) {
			advisor.setOrder(this.enableTx.<Integer>getNumber("order"));
		}
		return advisor;
	}

	@Bean
	@Role(BeanDefinition.ROLE_INFRASTRUCTURE)
	public TransactionInterceptor transactionInterceptor(TransactionAttributeSource transactionAttributeSource) {
		TransactionInterceptor interceptor = new TransactionInterceptor();
		interceptor.setTransactionAttributeSource(transactionAttributeSource);
		if (this.txManager != null) {
			interceptor.setTransactionManager(this.txManager);
		}
		return interceptor;
	}
}
```

⚠️ **TransactionAttributeSource** 빈 등록 부분 참고
- **AbstractTransactionManagementConfiguration** 클래스: AnnotationTransactionAttributeSource 빈 등록
```java
@Bean
@Role(BeanDefinition.ROLE_INFRASTRUCTURE)
public TransactionAttributeSource transactionAttributeSource() {
    ...
    // Accept protected @Transactional methods on CGLIB proxies, as of 6.0
    AnnotationTransactionAttributeSource tas = new AnnotationTransactionAttributeSource(false);
    // Apply default rollback rule, as of 6.2
    if (this.enableTx != null && this.enableTx.getEnum("rollbackOn") == RollbackOn.ALL_EXCEPTIONS) {
        tas.addDefaultRollbackRule(RollbackRuleAttribute.ROLLBACK_ON_ALL_EXCEPTIONS);
    }
    return tas;
    ...
}
```
- **AnnotationTransactionAttributeSource** 클래스: 트랜잭션 대상 핸들링
    - 기본적으로 org.springframework.transaction.annotation.Transactional 기반으로 동작 (**SpringTransactionAnnotationParser** 참고)
    - jakarta.transaction.Transactional, jakarta.ejb.TransactionAttribute 어노테이션 파싱 지원 관련 구성
```java
public class AnnotationTransactionAttributeSource extends AbstractFallbackTransactionAttributeSource {
    ...
    static {
        ClassLoader classLoader = AnnotationTransactionAttributeSource.class.getClassLoader();
        jtaPresent = ClassUtils.isPresent("jakarta.transaction.Transactional", classLoader);
        ejb3Present = ClassUtils.isPresent("jakarta.ejb.TransactionAttribute", classLoader);
    }
    ...
    public AnnotationTransactionAttributeSource() {
        if (jtaPresent || ejb3Present) {
            this.annotationParsers = CollectionUtils.newLinkedHashSet(3);
            this.annotationParsers.add(new SpringTransactionAnnotationParser());
            if (jtaPresent) {
                this.annotationParsers.add(new JtaTransactionAnnotationParser());
            }
            if (ejb3Present) {
                this.annotationParsers.add(new Ejb3TransactionAnnotationParser());
            }
        }
        else {
            this.annotationParsers = Collections.singleton(new SpringTransactionAnnotationParser());
        }
    }
}
    
``` 

- **SpringTransactionAnnotationParser** 클래스: org.springframework.transaction.annotation.Transactional 기반 처리
```java
public class SpringTransactionAnnotationParser implements TransactionAnnotationParser, Serializable {
    @Override
    public boolean isCandidateClass(Class<?> targetClass) {
        return AnnotationUtils.isCandidateClass(targetClass, Transactional.class);
    }

    @Override
    @Nullable
    public TransactionAttribute parseTransactionAnnotation(AnnotatedElement element) {
        AnnotationAttributes attributes = AnnotatedElementUtils.findMergedAnnotationAttributes(
                element, Transactional.class, false, false);
        if (attributes != null) {
            return parseTransactionAnnotation(attributes);
        } else {
            return null;
        }
    }
    ...
}
```

---

5. **BeanFactoryTransactionAttributeSourceAdvisor**
- 트랜잭션 대상(PointCut, TransactionAttributeSource)과 트랜잭션 처리(Advice, TransactionInterceptor) 연결
- **BeanPostProccessor**로 InfrastructureAdvisorAutoProxyCreator가 동작할 때
    - ApplicationContext에 등록된 빈이 proxy 생성이 필요한 대상인지 판단 (point cut): TransactionAttributeSource - @Transaction 대상
    - proxy로 처리되어야 하는 로직을 제공 (advice): TransactionInterceptor - 예외 발생시 트랜잭션 롤백

```java
    private final TransactionAttributeSourcePointcut pointcut = new TransactionAttributeSourcePointcut();

    public BeanFactoryTransactionAttributeSourceAdvisor() {
    }

    public void setTransactionAttributeSource(TransactionAttributeSource transactionAttributeSource) {
        this.pointcut.setTransactionAttributeSource(transactionAttributeSource);
    }

    public void setClassFilter(ClassFilter classFilter) {
        this.pointcut.setClassFilter(classFilter);
    }

    public Pointcut getPointcut() {
        return this.pointcut;
    }
```

---

6. **AutoProxyRegistrar**
- **InfrastructureAdvisorAutoProxyCreator** 빈 등록 (AOP 프록시 생성기)
    1. **ConfigurationClassPostProcessor**에서 **AutoProxyRegistrar**가 구현하고 있는 **ImportBeanDefinitionRegistrar**를 인식해 registerBeanDefinitions 호출
    2. 파라미터로 넘어온 importingClassMetadata는 @EnableTransactionManagement 정보를 갖고 있음
    3. @EnableTransactionManagement는 다른 조건들과 mode == AdviceMode.PROXY 조건에 해당하여 AopConfigUtils.registerAutoProxyCreatorIfNecessary(registry) 호출
    4. AopConfigUtils에서 **InfrastructureAdvisorAutoProxyCreator**가 존재하지 않는 경우에만 새로 레지스트리에 등록

```java
    public void registerBeanDefinitions(AnnotationMetadata importingClassMetadata, BeanDefinitionRegistry registry) {
    boolean candidateFound = false;

    for(String annType : importingClassMetadata.getAnnotationTypes()) {
        AnnotationAttributes candidate = AnnotationConfigUtils.attributesFor(importingClassMetadata, annType);
        if (candidate != null) {
            Object mode = candidate.get("mode");
            Object proxyTargetClass = candidate.get("proxyTargetClass");
            if (mode != null && proxyTargetClass != null && AdviceMode.class == mode.getClass() && Boolean.class == proxyTargetClass.getClass()) {
                candidateFound = true;
                if (mode == AdviceMode.PROXY) {
                    AopConfigUtils.registerAutoProxyCreatorIfNecessary(registry);
                    if ((Boolean)proxyTargetClass) {
                        AopConfigUtils.forceAutoProxyCreatorToUseClassProxying(registry);
                        return;
                    }
                }
            }
        }
    }

    if (!candidateFound && this.logger.isInfoEnabled()) {
        String name = this.getClass().getSimpleName();
        this.logger.info(String.format("%s was imported but no annotations were found having both 'mode' and 'proxyTargetClass' attributes of type AdviceMode and boolean respectively. This means that auto proxy creator registration and configuration may not have occurred as intended, and components may not be proxied as expected. Check to ensure that %s has been @Import'ed on the same class where these annotations are declared; otherwise remove the import of %s altogether.", name, name, name));
    }

}
```

```java
public abstract class AopConfigUtils {
    @Nullable
    public static BeanDefinition registerAutoProxyCreatorIfNecessary(BeanDefinitionRegistry registry) {
        return registerAutoProxyCreatorIfNecessary(registry, (Object) null);
    }

    @Nullable
    public static BeanDefinition registerAutoProxyCreatorIfNecessary(BeanDefinitionRegistry registry, @Nullable Object source) {
        return registerOrEscalateApcAsRequired(InfrastructureAdvisorAutoProxyCreator.class, registry, source);
    }

    @Nullable
    private static BeanDefinition registerOrEscalateApcAsRequired(Class<?> cls, BeanDefinitionRegistry registry, @Nullable Object source) {
        Assert.notNull(registry, "BeanDefinitionRegistry must not be null");
        if (registry.containsBeanDefinition("org.springframework.aop.config.internalAutoProxyCreator")) {
            BeanDefinition beanDefinition = registry.getBeanDefinition("org.springframework.aop.config.internalAutoProxyCreator");
            if (!cls.getName().equals(beanDefinition.getBeanClassName())) {
                int currentPriority = findPriorityForClass(beanDefinition.getBeanClassName());
                int requiredPriority = findPriorityForClass(cls);
                if (currentPriority < requiredPriority) {
                    beanDefinition.setBeanClassName(cls.getName());
                }
            }

            return null;
        } else {
            RootBeanDefinition beanDefinition = new RootBeanDefinition(cls);
            beanDefinition.setSource(source);
            beanDefinition.setRole(2);
            beanDefinition.getPropertyValues().add("order", Integer.MIN_VALUE);
            registry.registerBeanDefinition("org.springframework.aop.config.internalAutoProxyCreator", beanDefinition);
            return beanDefinition;
        }
    }
}
```

---

7. **InfrastructureAdvisorAutoProxyCreator**
- 컨테이너에 등록된 Advisor들을 스캔 후 각 Bean이 Advisor의 Pointcut 조건에 맞는 경우 AOP 프록시를 생성해 교체 등록
- BeanPostProccessor를 구현하고 있어 각 빈이 생성될 때 마다 위 기능 동작
    - 상속/구현 구조: InfrastructureAdvisorAutoProxyCreator : AbstractAdvisorAutoProxyCreator : AbstractAutoProxyCreator : SmartInstantiationAwareBeanPostProcessor : InstantiationAwareBeanPostProcessor : BeanPostProcessor
    1. AbstractAutoProxyCreator.postProcessBeforeInstantiation : TargetSource가 존재하는 경우, 프록시 생성
        - 그 외 보통 AbstractAutoProxyCreator.postProcessAfterInstantiation에서 생성
        - 두 경우 모두 getAdvicesAndAdvisorsForBean, createProxy로 흐름 동일
    2. AbstractAdvisorAutoProxyCreator.getAdvicesAndAdvisorsForBean : 대상 advisor 가져옴
    3. AbstractAdvisorAutoProxyCreator.createProxy (buildProxy) : 프록시 생성
        1. proxyTargetClass == true, 혹은 Class Target인 경우 : CGLIB 방식 ProxyFactory (클래스 상속, 신규 프록시 클래스 생성)
        2. 그 외 : Dynamic proxy 방식 ProxyFactory (인터페이스 구현체 구현, 메소드를 새로 구현)
        3. advisor build 및 매칭
        4. ProxyFactory.getProxy()
            5. CglibAopProxy.getProxy()
            6. JdkAopProxy.getProxy()
            -  classOnly인 경우, getProxyClass() 호출

```java 
public abstract class AbstractAutoProxyCreator extends ProxyProcessorSupport implements SmartInstantiationAwareBeanPostProcessor, BeanFactoryAware {
    @Nullable
    public Object postProcessBeforeInstantiation(Class<?> beanClass, String beanName) {
        Object cacheKey = this.getCacheKey(beanClass, beanName);
        if (!StringUtils.hasLength(beanName) || !this.targetSourcedBeans.contains(beanName)) {
            if (this.advisedBeans.containsKey(cacheKey)) {
                return null;
            }

            if (this.isInfrastructureClass(beanClass) || this.shouldSkip(beanClass, beanName)) {
                this.advisedBeans.put(cacheKey, Boolean.FALSE);
                return null;
            }
        }

        TargetSource targetSource = this.getCustomTargetSource(beanClass, beanName);
        if (targetSource != null) {
            if (StringUtils.hasLength(beanName)) {
                this.targetSourcedBeans.add(beanName);
            }

            Object[] specificInterceptors = this.getAdvicesAndAdvisorsForBean(beanClass, beanName, targetSource);
            Object proxy = this.createProxy(beanClass, beanName, specificInterceptors, targetSource);
            this.proxyTypes.put(cacheKey, proxy.getClass());
            return proxy;
        } else {
            return null;
        }
    }
}
```

```java
public abstract class AbstractAdvisorAutoProxyCreator extends AbstractAutoProxyCreator {
    @Nullable
    protected Object[] getAdvicesAndAdvisorsForBean(Class<?> beanClass, String beanName, @Nullable TargetSource targetSource) {
        List<Advisor> advisors = this.findEligibleAdvisors(beanClass, beanName);
        return advisors.isEmpty() ? DO_NOT_PROXY : advisors.toArray();
    }

    protected List<Advisor> findEligibleAdvisors(Class<?> beanClass, String beanName) {
        List<Advisor> candidateAdvisors = this.findCandidateAdvisors();
        List<Advisor> eligibleAdvisors = this.findAdvisorsThatCanApply(candidateAdvisors, beanClass, beanName);
        this.extendAdvisors(eligibleAdvisors);
        if (!eligibleAdvisors.isEmpty()) {
            try {
                eligibleAdvisors = this.sortAdvisors(eligibleAdvisors);
            } catch (BeanCreationException ex) {
                throw new AopConfigException("Advisor sorting failed with unexpected bean creation, probably due to custom use of the Ordered interface. Consider using the @Order annotation instead.", ex);
            }
        }

        return eligibleAdvisors;
    }

    protected List<Advisor> findCandidateAdvisors() {
        Assert.state(this.advisorRetrievalHelper != null, "No BeanFactoryAdvisorRetrievalHelper available");
        return this.advisorRetrievalHelper.findAdvisorBeans();
    }

    protected List<Advisor> findAdvisorsThatCanApply(List<Advisor> candidateAdvisors, Class<?> beanClass, String beanName) {
        ProxyCreationContext.setCurrentProxiedBeanName(beanName);

        List var4;
        try {
            var4 = AopUtils.findAdvisorsThatCanApply(candidateAdvisors, beanClass);
        } finally {
            ProxyCreationContext.setCurrentProxiedBeanName((String)null);
        }

        return var4;
    }
}
```

```java
public abstract class AbstractAutoProxyCreator extends ProxyProcessorSupport implements SmartInstantiationAwareBeanPostProcessor, BeanFactoryAware {
    protected Object createProxy(Class<?> beanClass, @Nullable String beanName, @Nullable Object[] specificInterceptors, TargetSource targetSource) {
        return this.buildProxy(beanClass, beanName, specificInterceptors, targetSource, false);
    }

    private Object buildProxy(Class<?> beanClass, @Nullable String beanName, @Nullable Object[] specificInterceptors, TargetSource targetSource, boolean classOnly) {
        BeanFactory advisors = this.beanFactory;
        if (advisors instanceof ConfigurableListableBeanFactory clbf) {
            AutoProxyUtils.exposeTargetClass(clbf, beanName, beanClass);
        }

        ProxyFactory proxyFactory = new ProxyFactory();
        proxyFactory.copyFrom(this);
        if (proxyFactory.isProxyTargetClass()) {
            if (Proxy.isProxyClass(beanClass) || ClassUtils.isLambdaClass(beanClass)) {
                for (Class<?> ifc : beanClass.getInterfaces()) {
                    proxyFactory.addInterface(ifc);
                }
            }
        } else if (this.shouldProxyTargetClass(beanClass, beanName)) {
            proxyFactory.setProxyTargetClass(true);
        } else {
            this.evaluateProxyInterfaces(beanClass, proxyFactory);
        }

        Advisor[] advisors = this.buildAdvisors(beanName, specificInterceptors);
        proxyFactory.addAdvisors(advisors);
        proxyFactory.setTargetSource(targetSource);
        this.customizeProxyFactory(proxyFactory);
        proxyFactory.setFrozen(this.freezeProxy);
        if (this.advisorsPreFiltered()) {
            proxyFactory.setPreFiltered(true);
        }

        ClassLoader classLoader = this.getProxyClassLoader();
        if (classLoader instanceof SmartClassLoader smartClassLoader) {
            if (classLoader != beanClass.getClassLoader()) {
                classLoader = smartClassLoader.getOriginalClassLoader();
            }
        }

        return classOnly ? proxyFactory.getProxyClass(classLoader) : proxyFactory.getProxy(classLoader);
    }
}
```

```java
class CglibAopProxy implements AopProxy, Serializable {
    public Object getProxy(@Nullable ClassLoader classLoader) {
        return this.buildProxy(classLoader, false);
    }

    private Object buildProxy(@Nullable ClassLoader classLoader, boolean classOnly) {
        if (logger.isTraceEnabled()) {
            logger.trace("Creating CGLIB proxy: " + String.valueOf(this.advised.getTargetSource()));
        }

        try {
            Class<?> rootClass = this.advised.getTargetClass();
            Assert.state(rootClass != null, "Target class must be available for creating a CGLIB proxy");
            Class<?> proxySuperClass = rootClass;
            if (rootClass.getName().contains("$$")) {
                proxySuperClass = rootClass.getSuperclass();
                Class<?>[] additionalInterfaces = rootClass.getInterfaces();

                for (Class<?> additionalInterface : additionalInterfaces) {
                    this.advised.addInterface(additionalInterface);
                }
            }

            this.validateClassIfNecessary(proxySuperClass, classLoader);
            Enhancer enhancer = this.createEnhancer();
            if (classLoader != null) {
                enhancer.setClassLoader(classLoader);
                if (classLoader instanceof SmartClassLoader) {
                    SmartClassLoader smartClassLoader = (SmartClassLoader) classLoader;
                    if (smartClassLoader.isClassReloadable(proxySuperClass)) {
                        enhancer.setUseCache(false);
                    }
                }
            }

            enhancer.setSuperclass(proxySuperClass);
            enhancer.setInterfaces(AopProxyUtils.completeProxiedInterfaces(this.advised));
            enhancer.setNamingPolicy(SpringNamingPolicy.INSTANCE);
            enhancer.setAttemptLoad(enhancer.getUseCache() && AotDetector.useGeneratedArtifacts());
            enhancer.setStrategy(KotlinDetector.isKotlinType(proxySuperClass) ? new ClassLoaderAwareGeneratorStrategy(classLoader) : new ClassLoaderAwareGeneratorStrategy(classLoader, undeclaredThrowableStrategy));
            Callback[] callbacks = this.getCallbacks(rootClass);
            Class<?>[] types = new Class[callbacks.length];

            for (int x = 0; x < types.length; ++x) {
                types[x] = callbacks[x].getClass();
            }

            ProxyCallbackFilter filter = new ProxyCallbackFilter(this.advised.getConfigurationOnlyCopy(), this.fixedInterceptorMap, this.fixedInterceptorOffset);
            enhancer.setCallbackFilter(filter);
            enhancer.setCallbackTypes(types);

            Object var23;
            try {
                var23 = classOnly ? this.createProxyClass(enhancer) : this.createProxyClassAndInstance(enhancer, callbacks);
            } finally {
                filter.advised.reduceToAdvisorKey();
            }

            return var23;
        } catch (IllegalArgumentException | CodeGenerationException ex) {
            throw new AopConfigException("Could not generate CGLIB subclass of " + String.valueOf(this.advised.getTargetClass()) + ": Common causes of this problem include using a final class or a non-visible class", ex);
        } catch (Throwable ex) {
            throw new AopConfigException("Unexpected AOP exception", ex);
        }
    }
}
```

```java
final class JdkDynamicAopProxy implements AopProxy, InvocationHandler, Serializable {
    public Object getProxy(@Nullable ClassLoader classLoader) {
        if (logger.isTraceEnabled()) {
            logger.trace("Creating JDK dynamic proxy: " + String.valueOf(this.advised.getTargetSource()));
        }

        return Proxy.newProxyInstance(this.determineClassLoader(classLoader), this.cache.proxiedInterfaces, this);
    }

    private ClassLoader determineClassLoader(@Nullable ClassLoader classLoader) {
        if (classLoader == null) {
            return this.getClass().getClassLoader();
        } else {
            if (classLoader.getParent() == null) {
                ClassLoader aopClassLoader = this.getClass().getClassLoader();

                for (ClassLoader aopParent = aopClassLoader.getParent(); aopParent != null; aopParent = aopParent.getParent()) {
                    if (classLoader == aopParent) {
                        return aopClassLoader;
                    }
                }
            }

            return classLoader;
        }
    }
}
```

```java
public abstract class AbstractAutoProxyCreator extends ProxyProcessorSupport implements SmartInstantiationAwareBeanPostProcessor, BeanFactoryAware {
    @Nullable
    public Object postProcessAfterInitialization(@Nullable Object bean, String beanName) {
        if (bean != null) {
            Object cacheKey = this.getCacheKey(bean.getClass(), beanName);
            if (this.earlyBeanReferences.remove(cacheKey) != bean) {
                return this.wrapIfNecessary(bean, beanName, cacheKey);
            }
        }

        return bean;
    }
}
```

---

8. TransactionIntercepter.invoke() / TransactionAspectSupport.invokeWithinTransaction()
   1. @Transactional 존재 여부 판단 (TransactionAttribute 생성)
   ```java
        TransactionAttribute txAttr = tas != null ? tas.getTransactionAttribute(method, targetClass) : null;
   ```
   2. TransactionManager 결정
   ```java
        TransactionManager tm = this.determineTransactionManager(txAttr, targetClass);
   ```
   3. 트랜잭션 생성 또는 기존 트랜잭션 참여, ThreadLocal에 저장
   ```java
        TransactionInfo txInfo = this.createTransactionIfNecessary(ptm, txAttr, joinpointIdentification);
   
        // createTransactionIfNecessary 내부
        txInfo.bindToThread();
   ```
   4. 실제 비즈니스 메서드 실행
   ```java
        retVal = invocation.proceedWithInvocation();
   ```
   5. 예외 발생 시 rollback 정책 판단
   ```java
        catch (Throwable ex) {
            this.completeTransactionAfterThrowing(txInfo, ex);
            throw ex;
        }
        ...
        if (txAttr.rollbackOn(ex)) {
            status.rollback();
        } else {
            status.commit();
        }
   ```
   6. 정상 종료 시 commit 실행
   ```java
        this.commitTransactionAfterReturning(txInfo);
        ...
        ptm.commit(txInfo.getTransactionStatus());
   ```
   7. ThreadLocal 트랜잭션 컨텍스트 제거
   ```java
        this.cleanupTransactionInfo(txInfo);
   ```

```java
public class TransactionInterceptor extends TransactionAspectSupport implements MethodInterceptor, Serializable {
    @Nullable
    public Object invoke(MethodInvocation invocation) throws Throwable {
        Class<?> targetClass = invocation.getThis() != null ? AopUtils.getTargetClass(invocation.getThis()) : null;
        Method var10001 = invocation.getMethod();
        Objects.requireNonNull(invocation);
        return this.invokeWithinTransaction(var10001, targetClass, invocation::proceed);
    }
}
```

```java
public abstract class TransactionAspectSupport implements BeanFactoryAware, InitializingBean {
    @Nullable
    protected Object invokeWithinTransaction(Method method, @Nullable Class<?> targetClass, final InvocationCallback invocation) throws Throwable {
        TransactionAttributeSource tas = this.getTransactionAttributeSource();
        TransactionAttribute txAttr = tas != null ? tas.getTransactionAttribute(method, targetClass) : null;
        TransactionManager tm = this.determineTransactionManager(txAttr, targetClass);
        if (this.reactiveAdapterRegistry != null && tm instanceof ReactiveTransactionManager rtm) {
            boolean isSuspendingFunction = KotlinDetector.isSuspendingFunction(method);
            boolean hasSuspendingFlowReturnType = isSuspendingFunction && "kotlinx.coroutines.flow.Flow".equals((new MethodParameter(method, -1)).getParameterType().getName());
            ReactiveTransactionSupport txSupport = (ReactiveTransactionSupport) this.transactionSupportCache.computeIfAbsent(method, (key) -> {
                Class<?> reactiveType = isSuspendingFunction ? (hasSuspendingFlowReturnType ? Flux.class : Mono.class) : method.getReturnType();
                ReactiveAdapter adapter = this.reactiveAdapterRegistry.getAdapter(reactiveType);
                if (adapter == null) {
                    String var10002 = String.valueOf(method.getReturnType());
                    throw new IllegalStateException("Cannot apply reactive transaction to non-reactive return type [" + var10002 + "] with specified transaction manager: " + String.valueOf(tm));
                } else {
                    return new ReactiveTransactionSupport(adapter);
                }
            });
            return txSupport.invokeWithinTransaction(method, targetClass, invocation, txAttr, rtm);
        } else {
            PlatformTransactionManager ptm = this.asPlatformTransactionManager(tm);
            String joinpointIdentification = this.methodIdentification(method, targetClass, txAttr);
            if (txAttr != null && ptm instanceof CallbackPreferringPlatformTransactionManager cpptm) {
                ThrowableHolder var35 = new ThrowableHolder();

                Object result;
                try {
                    result = cpptm.execute(txAttr, (status) -> {
                        TransactionInfo txInfo = this.prepareTransactionInfo(ptm, txAttr, joinpointIdentification, status);

                        Object runtimeException;
                        try {
                            try {
                                Object retVal = invocation.proceedWithInvocation();
                                if (retVal != null && vavrPresent && TransactionAspectSupport.VavrDelegate.isVavrTry(retVal)) {
                                    retVal = TransactionAspectSupport.VavrDelegate.evaluateTryFailure(retVal, txAttr, status);
                                }

                                runtimeException = retVal;
                                return runtimeException;
                            } catch (Throwable ex) {
                                if (txAttr.rollbackOn(ex)) {
                                    if (ex instanceof RuntimeException) {
                                        RuntimeException runtimeException = (RuntimeException) ex;
                                        throw runtimeException;
                                    }

                                    throw new ThrowableHolderException(ex);
                                }
                            }

                            var35.throwable = ex;
                            runtimeException = null;
                        } finally {
                            this.cleanupTransactionInfo(txInfo);
                        }

                        return runtimeException;
                    });
                } catch (ThrowableHolderException ex) {
                    throw ex.getCause();
                } catch (TransactionSystemException var26) {
                    if (var35.throwable != null) {
                        this.logger.error("Application exception overridden by commit exception", var35.throwable);
                        var26.initApplicationException(var35.throwable);
                    }

                    throw var26;
                } catch (Throwable ex2) {
                    if (var35.throwable != null) {
                        this.logger.error("Application exception overridden by commit exception", var35.throwable);
                    }

                    throw ex2;
                }

                if (var35.throwable != null) {
                    throw var35.throwable;
                } else {
                    return result;
                }
            } else {
                TransactionInfo txInfo = this.createTransactionIfNecessary(ptm, txAttr, joinpointIdentification);

                Object retVal;
                try {
                    retVal = invocation.proceedWithInvocation();
                } catch (Throwable ex) {
                    this.completeTransactionAfterThrowing(txInfo, ex);
                    throw ex;
                } finally {
                    this.cleanupTransactionInfo(txInfo);
                }

                if (retVal != null && txAttr != null) {
                    TransactionStatus status = txInfo.getTransactionStatus();
                    if (status != null) {
                        label195:
                        {
                            if (retVal instanceof Future) {
                                Future<?> future = (Future) retVal;
                                if (future.isDone()) {
                                    try {
                                        future.get();
                                    } catch (ExecutionException ex) {
                                        Throwable cause = ex.getCause();
                                        Assert.state(cause != null, "Cause must not be null");
                                        if (txAttr.rollbackOn(cause)) {
                                            status.setRollbackOnly();
                                        }
                                    } catch (InterruptedException var29) {
                                        Thread.currentThread().interrupt();
                                    }
                                    break label195;
                                }
                            }

                            if (vavrPresent && TransactionAspectSupport.VavrDelegate.isVavrTry(retVal)) {
                                retVal = TransactionAspectSupport.VavrDelegate.evaluateTryFailure(retVal, txAttr, status);
                            }
                        }
                    }
                }

                this.commitTransactionAfterReturning(txInfo);
                return retVal;
            }
        }
    }
}
```