---
title: Java Deep&Shallow Copy
tags:
---



In Java, the **ArrayList clone()** method creates a shallow copy of the list in which only object references are copied. 

# Shallow Copy

Let us see the internal implementation of the *clone* method.

```java
public Object clone() {
    try {
        ArrayList<?> v = (ArrayList<?>) super.clone();
        v.elementData = Arrays.copyOf(elementData, size);
        v.modCount = 0;
        return v;
    } catch (CloneNotSupportedException e) {
        // this shouldn't happen, since we are Cloneable
        throw new InternalError(e);
    }
}
```

The following Java program creates a **shallow copy of an arraylist** using `clone()` method.

```java
ArrayList<String> arrayListObject = new ArrayList<>(List.of("A", "B", "C", "D"));
ArrayList<String> arrayListClone =  (ArrayList<String>) arrayListObject.clone();
```

# Creating a Deep Copy of *ArrayList*

Creating a deep copy of a collection is rather easy. We need to create a new instance of collection and copy all elements from the given collection into the cloned collection – one by one. Note that we will copy the element’s clone in the cloned collection.

```java
ArrayList<Employee> employeeList = new ArrayList<>();
ArrayList<Employee> employeeListClone = new ArrayList<>();
Collections.copy(employeeList, employeeListClone);
```





Java program to create a **deep copy of an arraylist**.

```java
ArrayList<Employee> employeeList = new ArrayList<>();
employeeList.add(new Employee(1l, "adam", new Date(1982, 02, 12)));
ArrayList<Employee> employeeListClone = new ArrayList<>();
Collections.copy(employeeList, employeeListClone);
//Modify the list item in cloned list - it should affect the original list item
employeeListClone.get(0).setId(2l);
employeeListClone.get(0).setName("brian");
employeeListClone.get(0).getDob().setDate(13);;
System.out.println(employeeList);
System.out.println(employeeListClone);
```



Program output. Notice that even after changing the values of `Employee` object in `employeeListClone`, original employee list `employeeList` is not changed.

```
[Employee [id=1, name=adam, dob=Sun Mar 12 00:00:00 IST 3882]]
[Employee [id=2, name=brian, dob=Mon Mar 13 00:00:00 IST 3882]]
```

