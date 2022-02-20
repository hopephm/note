package com.spring.aop.aspects;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.*;
import org.aspectj.lang.reflect.MethodSignature;
import org.springframework.stereotype.Component;

import java.lang.reflect.Method;
import java.util.Arrays;

@Aspect
@Component
public class CheckAspect {

//  @Before("@annotation(com.spring.aop.aspects.CheckSomething)")
//  public void checkSomethingBefore(JoinPoint joinPoint) {
//    System.out.println("Before execution - Roles: " + Arrays.toString(getRoles(joinPoint)));
//  }
//
//  @AfterReturning(pointcut = "@annotation(com.spring.aop.aspects.CheckSomething)")
//  public void checkSomethingAfter(JoinPoint joinPoint) {
//    System.out.println("After execution - Roles: " + Arrays.toString(getRoles(joinPoint)));
//
//  }
//
//  @AfterThrowing(pointcut = "@annotation(com.spring.aop.aspects.CheckSomething)", throwing = "ex")
//  public void checkSomethingAfterThrowingAnException(JoinPoint joinPoint, Exception ex) {
//    System.out.println("After throwing an exception - Roles:" + Arrays.toString(getRoles(joinPoint)) + ex);
//  }

  @Around("@annotation(com.spring.aop.aspects.PrintAfterMethod)")
  public Object checkSomethingAround(ProceedingJoinPoint joinPoint) throws Throwable {
//    System.out.println("Before in Around execution. - Roles: " + Arrays.toString(getRoles(joinPoint)));
    Object result = joinPoint.proceed();
    System.out.println("hello world!");
    return result;
  }


//  public String[] getRoles(JoinPoint joinPoint) {
//    MethodSignature signature = (MethodSignature) joinPoint.getSignature();
//    Method method = signature.getMethod();
//    CheckSomething myAnnotation = method.getAnnotation(CheckSomething.class);
//    return myAnnotation.roles();
//  }
}
