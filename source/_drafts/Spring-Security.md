---
title: Spring Security
tags:
---

![image-20220303125252342](/home/lyk/.config/Typora/typora-user-images/image-20220303125252342.png)





Security的机制：

1. 提供一个`AbstractSecurityWebApplicationInitializer`，实现了`WebApplicationInitializer`， 用于拦截请求(因此会被Spring扫描到)。 该抽象类已经默认实现了`onStartup()`,

   ```java
   public abstract class AbstractSecurityWebApplicationInitializer implements WebApplicationInitializer;
   ```

   * 之前提到过，Spring会自动扫描所有`WebApplicationInitializer`的实现类，多个实现类可以共存
   * 另一个`WebApplicationInitializer`是` Ab stractAnnotationConfigDispatcherServletInitializer`，仅负责` DispatcherServlet`的初始化。 

2. 接着就是一系列的代理，最终代理到Spring应用上下文的`FilterChainProxy`， 这个Bean已经被Spring创建好了

3. 因此，要使用Spring Security, 我们只需要继承`AbstractSecurityWebApplicationInitializer`， 并且配置一下maven依赖。 

4. 要对Security做配置，需要继承`WebSecurityConfigurerAdapter`， override其`configure()`方法



## 继承WebSecurityConfigurerAdapter

这里是一个继承类

```java
@Configuration
@EnableWebMvcSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {

  @Override
  protected void configure(HttpSecurity http) throws Exception {
    http
      .formLogin()
        .loginPage("/login")
      .and()
        .logout()
          .logoutSuccessUrl("/")
      .and()
      .rememberMe()
        .tokenRepository(new InMemoryTokenRepositoryImpl())
        .tokenValiditySeconds(2419200)
        .key("spittrKey")
      .and()
       .httpBasic()
         .realmName("Spittr")
      .and()
      .authorizeRequests()
        .antMatchers("/").hasAnyRole("USER")
        .antMatchers("/spitter/me").authenticated()
        .antMatchers(HttpMethod.POST, "/spittles").authenticated()
        .anyRequest().permitAll()
//    .and()
//            .requiresChannel() //用于https加密通道
//            .antMatchers("/spitter/register").requiresSecure()
//    .and().csrf().disable()
    ;

  }

  @Override
  protected void configure(AuthenticationManagerBuilder auth) throws Exception {
    auth
      .inMemoryAuthentication() //这里把数据存到内存中， 还可以放到数据库内，或者用LDAP
        .withUser("user").password("password").roles("USER");
  }


}
```

## 

## 基于web

Security提供了抽象类`AbstractSecurityWebApplicationInitializer`  实现了`WebApplicationInitializer`，

```java
public abstract class WebSecurityConfigurerAdapter implements WebSecurityConfigurer<WebSecurity>;
```

### login

```java
  protected void configure(HttpSecurity http) throws Exception {
    http
      .formLogin()
//        .loginPage("/login")
      .and()
        .logout()
          .logoutSuccessUrl("/")
      .and()
      .rememberMe()
        .tokenRepository(new InMemoryTokenRepositoryImpl())
        .tokenValiditySeconds(2419200)
        .key("spittrKey")
      .and()
       .httpBasic()
         .realmName("Spittr")
      .and()
      .authorizeRequests()
        .antMatchers("/").hasAnyRole("USER")
        .antMatchers("/spitter/me").authenticated()
        .antMatchers(HttpMethod.POST, "/spittles").authenticated()
        .anyRequest().permitAll()
//    .and()
//            .requiresChannel()
//            .antMatchers("/spitter/register").requiresSecure()
//    .and().csrf().disable()
    ;

  }
```



登录页面：`localhost/login`

      .formLogin()
        .loginPage("/login")
      .and()



如果不提供

```
      .formLogin()
        .loginPage("/login")
      .and()
```

那么不能访问`/login`。 访问其他页面时（如`lovalhost/`），会弹出一个http对话框。 



如果是：

```java
      .formLogin()
    //    .loginPage("/login")
      .and()
```

spring会自动创建一个登录页面



总而言之，每个页面都有权限控制，如果用户没有权限，就会自动重定向到登录页面。

* “所有页面”包括`logout`， 假如`logout`退出后重定向的页面，用户没有权限，那么用户还会被重定向到登录页面

### rememberme

```java
      .rememberMe()
        .tokenRepository(new InMemoryTokenRepositoryImpl())
        .tokenValiditySeconds(2419200)
        .key("spittrKey")
```

如果用户被记住，则再次访问页面不需要权限

可以看到，rememberme采用token。 第一次登录时，token会存储在后端。 浏览器每次请求都会带上token, 后端收到后进行比对，进行验证

* token是一种cookie



此外，还有一种cookie是SESSIONID，服务端每一次信息交互都会传一次SESSIONID,不管登没登录。 

### BasicAuth

httpBasic是一种认证方式：

```java
       .httpBasic()
         .realmName("Spittr")
      .and()
      .authorizeRequests()
        .antMatchers("/").hasAnyRole("USER")
        .antMatchers("/spitter/me").authenticated()
        .antMatchers(HttpMethod.POST, "/spittles").authenticated()
        .anyRequest().permitAll()
```

添加认证后， 浏览器访问`/spitter/me`  会需要权限认证，如果没有权限的话，会跳转到登录页面。 对于HttpBasic认证，我们在postman请求时，选择Basic Auth, 可以在请求头中加` Authorization`字段作为认证信息。 认证信息会经过编码（只是编码，而不是加密），默认用的是basic64：

请求头中的` Authorization`字段：

```
 dXNlcjpwYXNzd29yZA==
```



Base64解码后：

```
user:password
```

正是登录所需的帐号密码

### https

```java
    .and()
            .requiresChannel()
            .antMatchers("/spitter/register").requiresSecure()
```

指定该url需要用https

## 基于方法

![image-20220303151012179](/home/lyk/.config/Typora/typora-user-images/image-20220303151012179.png)

* spring自带注解

  ```java
  @Secured({"ROLE_SPITTER", "ROLE_ADMIN"})
  ```

  ```java
  @EnableGlobalMethodSecurity(securedEnabled=true)
  ```

  

* JSR-250

  ```java
  @RolesAllowed("ROLE_SPITTER")
  ```

  ```java
  @EnableGlobalMethodSecurity(jsr250Enabled=true)
  ```

  

* 表达式驱动的注解

  ```java
  @PreAuthorize("(hasRole('ROLE_SPITTER') and #spittle.text.length() le 140) or hasRole('ROLE_PREMIUM')")
  ```

  ```java
  @EnableGlobalMethodSecurity(prePostEnabled=true)
  ```

  
