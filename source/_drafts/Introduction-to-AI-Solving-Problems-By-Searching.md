---
title: 'Chapter 3: Solving Problems By Searching'
tags: Introduction to Artificial Intelligence
categories: Artificial Intelligence 
mathjax: true
---

Outline:

* Intro
* Problem-Solving Agents
* Example Problems
* Searching For Solutions
* Uniformed Search Strategies
* Informed(Heuristic) Search Strategies( // TO DO )
* Bibliographical and Historical Notes

<!--more-->

# Intro

* goal-based agent.
  * **problem-solving agents** use  **atomic** repretations, 即将世界看作一个不可分割,没有内在结构的整体.  本章描述problem-solving agents
  * planning  agents: 也属于goal-based agent. use more advanced **factored** or **structured** representations 
* **uninformmed** search algorithms: algoritms that are given no information about the problem other than its definition
  * some of them can solve any solvable problem 
  *  none of them work efficiently
* **informed / heuristic** search algorithm: otherwise
  * know whether one non-goal state is "more promising" than another
  * can do quite well given some guidance on what to look for solutions
* 本章中, solution总是一条 *fixed sequence* of actions, agent在未来不会受percepts的影响

# Problem-Solving Agents

* Assumption: the  environment is **observable** , **known**,  **deterministic**
  * **observable**: agent knows the current state
  * **discrete**: at any given state there are only finite many actions to choose from
  * **known**: agent knows which state is reached by each action.
  *   **deterministic**: each action has exactly one outcome
* *Under these assumptions, the solution of any problem is a fixed sequence of action*
  * 本章中,由于环境是 known, deterministic的, 因此agent知道行动的结果和行动后的percepts, action之后只有一个percept,因此只有一个后继action,因此solution是一条固定行动序列.
    *  known, deterministic意味着环境是静态的, agent知道action的结果并且也确定能达到这个结果
  * 否则, 若agent对未来的percepts不能确定,后继action也不能确定,solution就会 branching

* problem solving的步骤

  1. formulate:

     * **goal  formulation**
       * goal: a set og world states --- exactly those states in which the goal is satisfied
       * agent的任务就是find out how to act now and in the future 来达到 a goal state

     * **problem formulation**
       * the process of deciding  what actions and states to consider, given a goal. 
         * 即确定思维的层次,是要在 detail level还是在 higher abstract level

  2. **search**:
     * the process of looking for a sequence of action that reaches the goal
     * input: a problem
     * output: a **solution**

  3. execution
     * while the agent is executing the solution sequence it *ignores its percepts* when choosing an action because <u>it knows in advance what they might be</u>
     * 可以认为agent是闭着眼睛根据solution行动,这种系统也被称为**open-loop** system, because ignoring the percepts breaks  the loop between agent and environvent.    

## Well - defined problems and solutions

A **problem** can bedefined formally by 5 components:

* The **initial state**: $In(Arad)$

* **actions**: $\{ Go(Sibiu), Go(Timisoara), Go(Zerind) \}$

  * each action is **applicable**

* **transition model**: $RESULT(s,a)$

  * **sueecssor**: any state reachable from a given state by a single action. e.g. $RESULT(In(Arad),Go(Timisiara)) = In(Zerid)$

  * **state space**: the initial sate, actions, and transition model together define the **state space** of the problem.
    *  The state space forms a directed graph (有向图). state 为节点, action为边

* **goal test:**

  * sometimes there is an explicit set of possible goal states,and the test simply checks whether the given state is in one of them.
  * sometimes the goal is specified by an abstract property rather than emurated set of states, such as "checkmate"(象棋中的""将军"")

* **path cost**:

  * a path cost function that assigns a numeric cost to each path.
    * An **optimal solution** has the lowst path cost among all solutions
  *  **step cost**: $c(s,a,s')$
    * the step cost of  taking action $a$ in state $s$ to reach state $s'$

The preceding elements define a problem and can be gathered into a single data structure that is given as input to a problem-solving algorithm

## Formulating problems

* abstraction: remobing detail from a representation
  * *valid*: we can expand any abstract solution into a solution in a more detailed world
  * *useful*: carrying out each of the actions in the solution is easier than the origin problem
  *  the choice of good abstraction thus involves removing as much detail as possible while retaining validity and utility

# Example Problems

* *toy problem*: 抽象, 泛化, 形式化的问题

* *real-world problem*: 实际问题, 不一定形式化

## Toy problems

* vacuum world problem
* sliding-block puzzles: NPC
* 8-queens problem
  * incremental forlmulation:  initial state为空; 每个action是添加一名皇后
  *  complete-state formulation: initial state为8个皇后,每个action是皇后的移动

## Real-world problems

* route-finding problem:
  * Touring problems: Visit every city at least once, starting and ending in Bucharset
  * traveling salesperson problem(TSP): a touring problem in whcih each city must be visited exactly once. The aim is to find shortest tour
    * NP-hard
  * VLSI( Very Large Scale Integration ) problem
  * Robot navigation: 是路由选择问题的泛化, 该问题的状态空间是连续的
  * Automatic assembly sequencing: to find a order to assemble the parts  of some object
    * protein design: 一种自动装配问题

# Searching For Solutions

* **search tree**: the possible action sequence starting at the initial state form a search tree with the initial state as the root
* **node**: correspond to states in the state space of the problem
* **expanding**: applying each legal action to the current state
* **gengerating**: gengerating the current state
* **frontier**: the set of <u>all leaf nodes available for expansion</u> at any given point

* **search strategy**: 对要expansion的节点的选择策略
  * 搜索算法的基本结构都相同,区别在于search strategy

* **explored set**: remembering all explored node
  * *algorithms tha forget their history are doomed to repeat it*
  * newly generated nodes  that mach previously gengerated nodes --- ones in the explored set or the frontier ---- can be discarded instead of being added to the frontier
  * 可用 hash  table实现,确保插入和检索都在常数时间
* **Tree search**: 普通的search, 可能有redundant paths
* **Graph search**: 采用explored set以避免redundant paths

## Measuring oroblem-solving performance

we can evaluate an algorithms's performance in four ways:

* **Completeness**:  在solution存在的情况下, 算法是否确保找到solution
* **Optimality**:算法是否找到了 optimal solution(  lowest path cost )
* **Time complexity**
* **Time complexity**
  * $b$: the branching factor or maximum number of successors of any node
  * $d$: the depths of the shallowest goal node
  * $m$: the maximum length of any path in the search



算法代价:

* search cost: 时间和空间复杂度
* total cost: search cost + paths cost of the solution found

# Uniformed Search Strategies

## BFS 

* Expand shallowest unexpanded node

###  Properties

* Complete: Yes ( if $b$ and $d$ is finite)
* Optimal: optimal if the path cost us a nondecreasing function of the depth of the node
* Time: $ O(b^d )$, i.e., exp. in $d$
  * $1 + b + b^2 + b^3 + . . . + b^d  = O(b^d )$
* Space: $O(b^d)$
  * (keeps every node in memory)
  * $O(b^{d-1})$ nodes in the *explored set*
  * $O(b^d)$ nodes in the frontier



## Uniform-cost search

* uniform-cost search expands the node $n$ with the *lowest path cost* $g(n)$
* step-costs are non negative

### Properties

Let $C^*$ be the cost of the optimal solution



* Complete: Yes, if step cost ≥ some small positive constant $\epsilon$
  * 因为不能出现零环
* Time: $O(b^{1+ \lfloor C^* / \epsilon \rfloor})$
* Space: $O(b^{1+ \lfloor C^* / \epsilon \rfloor})$
* Optimal: Yes
  * whenever uniform-cost search selects a node $n$ for expansion, the optimal path  that node has been found
  * because step-costs are non negative, paths never get shorter
  * *uniform-cost search expands nodes in order of their optimal path cost*
  * thus, the first goal node selected for expansion must be the optimal solution

## DFS

* Expand deepest unexpanded node

### Properties

The properties if dfs depend strongly on whether the graph-search or tree-search version is used 

* Complete:

  * in finite-depth spaces:

    * 图搜索: yes

      * 可以确保没有重复状态和冗余的边,因此complete; 

    * 树搜索: no

      * 可能出现loops, 无法确保complete

      * 树搜索可以modify,以检查重复状态,但仍然无法去除冗余边

  * in infinite-depth spaces: both versions are No

* Optima: both versions are No

* Time: $O(b^m )$

  * $1 + b + b^2 + b^3 + . . . + b^m  = O(b^m )$

  * terrible if $m$ is much larger than $d$

* Space: $O(bm)$, i.e., linear space



## Depth-limited search

limit the maximum depth of the depth-first  search to avoid DFS's failure in infinite space

* $l$ : the depth limit
  * if $l < d$, incompleteness
  * if $l > d$, nonoptimal
* DFS 可看作  DLS 的 $l = \infty$ 的特例



## Iterative deepening search

try depth-limited search with increasing limit, restart the search at each time

### Properties
* Complete: Yes, when $b$ is finite
  * like BFS
* Optimal: Yes, if the path cost us a nondecreasing function of the depth of the node
  * like BFS
* Time: $O(b^d)$
  * $db + (d-1)b^2  + \dots + b^d = O(b^d )$
    small space as depth-first search
* Space: $O(bd)$
  * like DFS ( $m == d$ )

## Bidirectional search

从goal node和 init node分别同时开始遍历

* goal  test: the frontiers of the two searches intersect
  * the first solution found may not be optimal

### Properties

* Time: $O(b^{d/2})$
  * $db + (d-1)b^2  + \dots + b^d = O(b^d )$
    small space as depth-first search
* Space: $O(b^{d/2})$

## Comparing uniformed search strategies

| Criterion | BFS              | Unifor-Cost                                | DFS   | Depth limited      | Iterative Deepening |
| --------- | ---------------- | ------------------------------------------ | ----- | ------------------ | ------------------- |
| Complete? | $\mathrm{Yes}^*$ | $\mathrm{Yes}^*$                           | No    | Yes, if $l \geq d$ | Yes                 |
| Optimal?  | $\mathrm{Yes}^*$ | $\mathrm{Yes}^*$                           | No    | No                 | $\mathrm{Yes}^*$    |
| Time      | $b^d$            | $O(b^{1+ \lfloor C^* / \epsilon \rfloor})$ | $bm$  | $bl$               | $bd$                |
| Space     | $b^d$            | $O(b^{1+ \lfloor C^* / \epsilon \rfloor})$ | $b^m$ | $b^l$              | $b^d$               |

# Informed(Heuristic) Search Strategies

select a node for expansion based on an **evaluation function** $f(n)$, which is constructed as a cost estimate

* heuristic function: $ h(n)$ = estimate of cost from n to the closest goal
  * $f(n)$的一部分
  *  heuristic function  are the most common form in which additional knowledge of the problem is imparted to the search problrm
  *  唯一的约束: $h(n) ≥ 0$, and $h(G) = 0$ for any goal $G$. 

## Greedy search

Greedy search expands the node that **appears** to be closest to goal

* $f(n)=g(n)$

### Properties

* Complete:  No
  * no, even in a finite state space.
    * can get stuck in loops, e.g.,
* Optimal: No
* Time and Space:  $O(b^m )$
  * but a good heuristic can give dramatic improvement

## $A^*$ search

* $f(n)=g(n) + h(n)$
* $f(n)$ = estimated cost of the cheapest solution through $n$

### Properties

* $A^*$ search uses an **admissible** heuristic

  * i.e., $h(n) \leq h^*(n)$ where $h^*(n)$ is the true cost from $n$.

*  for graph-search: use  **consistent**  heuristic

  * A heuristic is **consistent** if $ h(n) \leq c(n, a, n') + h(n' ) $

  * If $h$ is **consistent**, we have
    $$
    f (n') = g(n') + h(n') \\
    \qquad \qquad \qquad \qquad = g(n) + c(n, a, n! ) + h(n ! ) \\
    \qquad ≥ g(n) + h(n) \\
    = f (n)
    $$
    I.e., $f (n)$ is nondecreasing along any path.

  * consistent 是比 admissible 更强的条件

  

 

### Optimality

*the tree search version of* $A^*$ *is optimal if*  $h(n)$ *is  admissible, wyhile the graph-search version is optimal if*  $h(n)$ *is  consistent*

我们现在只证第二点:

1. 证明 $f (n)$ is nondecreasing along any path.
   * 前已证
2. 证明: *whenever* $A^*$ *selects a node n for expansion, the optimal path to that node has been found*
3. 因此,找到的第一个goal node for expansion必然是optimal solution. 因为此时$h(n) = 0$, $f$ = true cost, 且由于$f$非递减, 之后找到的goal nodes will  be at least expensive

## Memory- bounded heuristic search

# Heuristic Functions

## The effect of Heuristic accuracy on performance

## Generating admissible heuristics from relaxed problems

## Generating admissible heuristics from subproblems: Pattern databases

## Learn heuristics from experiences

# Bibliographical and Historical Notes

