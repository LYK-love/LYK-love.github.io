---
title: Probability
tags:
---





Another probability question that causes many people difficulty is the children's gender puzzle: I tell you I have two children and that (at least) one of them is a boy, and ask you what you think is the probability that I have two boys. Many people, when they hear this puzzle for the first time, give the answer 1/2, reasoning that there is an equal likelihood that my other child is a boy or a girl. But this is not correct. Based on what you know, you should conclude that I am actually twice as likely to have a boy and a girl as I am to have two boys. So your right answer to my question is not 1/2 but 1/3.



To go back to the original puzzle now, in order of birth, there are four possible gender combinations for my children: BB, GG, BG, GB. Each is equally likely. (To avoid niggling complications, I'm assuming each gender is equally likely at birth, and ignore the possibility of identical twins, etc.) So, if all I told you was that I have two children, you would (if you are acting rationally) say that the probability I have two boys is 1/4. But I tell you something else: that at least one of my children is a boy. That eliminates the GG possibility.

So now you know the possible gender combinations are BB, BG, GB. Of these three possibilities, in two of them I have a boy and a girl, and in only one do I have two boys, so you should calculate the probability of my having two boys to be 1 out of 3, namely 1/3.



> Before I explain the answer, I should clear up a confusion that many people have about problems such as this, which are about what is known as *epistemic probability*. The probability being discussed here is not some unchangable feature of the world, like the probability of throwing a double six with a pair of honest dice. After all, I have already had my two children, and their genders have long been determined. At issue is what probabilities *you attach* to *your knowledge* of my family. As is the case with most applications of probability theory outside the casinos, the probability here is a measure of an individual's knowledge of the world, and different people can, and often do, attach different probabilities to the same event. Moreover, as you acquire additional information about an event, the probability you attach to it can change.







I tell you I have two children, and (at least) one of them is a boy born on a Tuesday. What probability should you assign to the event that I have two boys?



The crux of the matter is that Foshee's variant seems at first glance to be a minor twist on the original one, but it's actually significantly different. The property it focuses on is not gender, but the combination property *gender* + *day of birth*. That makes the mathematics very different, as I'll now show. Instead of just the two genders, B and G, of the original puzzle, there are now 14 possibilities for each child:

> B-Mo, B-Tu, B-We, B-Th, B-Fr, B-Sa, B-Su
>
> G-Mo, G-Tu, G-We, G-Th, G-Fr, G-Sa, G-Su

When I tell you that one of my children is a boy born on a Tuesday, I eliminate a number of possible combinations, leaving the following:

> First child B-Tu, second child: B-Mo, B-Tu, B-We, B-Th, B-Fr, B-Sa, B-Su, G-Mo, G-Tu, G-We, G-Th, G-Fr, G-Sa, G-Su.
>
> Second child B-Tu, first child: B-Mo, B-We, B-Th, B-Fr, B-Sa, B-Su, G-Mo, G-Tu, G-We, G-Th, G-Fr, G-Sa, G-Su.

Notice that the second row has one fewer members than the first, since the combination B-Tu + B-Tu already appears in the first row.

Altogether, there are 14 + 13 = 27 possibilities. Of these, how many give me two boys? Well, just count them. There are 7 in the first row, 6 in the second row, for a total of 13 in all. So 13 of the 27 possibilities give me two boys, giving that answer of 13/27. (As in the original problem, you have to assume all the combinations are equally likely. In the case of birth days, this is actually not the case, since more babies are born on Fridays, and fewer on weekends, due to the desire of hospital doctors to have weekends as free as possible of duties.)

https://www.maa.org/external_archive/devlin/devlin_04_10.html
