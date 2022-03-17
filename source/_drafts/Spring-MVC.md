---
title: Spring MVC
tags:
---

#   异常

如果出现任何没有映射
的异常,响应都会带有500状态码,但是,我们可以通过映
射SpittleNotFoundException对这种默认行为进行变更



@Controller等价于@Component

![image-20220303125606007](/home/lyk/.config/Typora/typora-user-images/image-20220303125606007.png)

5： 视图解析器，如 JSP,  Thymythef

6: DispatcherServlet生成View对象返回给浏览器

# Servlet





![image-20220303124755212](/home/lyk/.config/Typora/typora-user-images/image-20220303124755212.png)

只要实现了`WebApplicationInitializer`接口，spring就会自动跟踪到这个实现类，并调用其`onStartup()`方法. Spring默认为我们创建了`AbstractAnnotationConfigDispatcherServletInitializer`抽象类，这个抽象类已经帮我们实现了创建`DispatcherServlet`的方法。 因此我们只要写创建我们所需的servlet和filter的方法

* `WebApplicationInitializer`允许有多个实现类，它们都会被Spring发现



![image-20220303130230357](/home/lyk/.config/Typora/typora-user-images/image-20220303130230357.png)

再配置两个上下文：

![image-20220303130252964](/home/lyk/.config/Typora/typora-user-images/image-20220303130252964.png)



Servlet3支持这样的Java配置，之前的版本只能用xml配置

获得请求的输入：

*  查询参数： 

  ？max =34   

  @RequestParam("max")

* 路径参数:  

  占位符"/{name}" 

  @PathVariabke("name")

* 表单参数:   参数名与对象字段名相同 
