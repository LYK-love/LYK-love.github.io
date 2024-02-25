---
title: 'Sora: The Text-to-Video Model'
tags:
---

[Tech report: Sora](Video generation models as world simulators)



![Figure Patches](https://images.openai.com/blob/1d2955dd-9d05-4f33-b346-be531d2a7737/figure-patches.png?trim=0,0,0,0&width=10&height=10&quality=50)

# Tokenization

We take inspiration from large language models which acquire generalist capabilities by training on internet-scale data.[13](https://openai.com/research/video-generation-models-as-world-simulators#fn-13),[14](https://openai.com/research/video-generation-models-as-world-simulators#fn-14) The success of the LLM paradigm is enabled in part by the use of tokens that elegantly unify diverse modalities of text—code, math and various  natural languages. In this work, we consider how generative models of  visual data can inherit such benefits. Whereas LLMs have text tokens,  Sora has visual *patches*. Patches have previously been shown to be an effective representation for models of visual data.

We find that patches are a highly-scalable and effective representation for training generative models on diverse types of videos and images.



![image-20240220155640297](/Users/lyk/Library/Application Support/typora-user-images/image-20240220155640297.png)

## Video compression network



![image-20240220155657443](/Users/lyk/Library/Application Support/typora-user-images/image-20240220155657443.png)

