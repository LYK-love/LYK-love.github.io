---
title: Segment Anything
tags:
---

Source:

* [Masked Autoencoders (MAE)]()
* [Vision Transformer (ViT)]()
* [Segment Anything blog](https://ai.meta.com/blog/segment-anything-foundation-model-image-segmentation/)
* [Youtube video: Segment Anything - Model explanation with code](https://youtu.be/eYhvJR4zFUM?si=Sxd0iDZc6jxksUYv)
  * [-->Slides](https://github.com/hkproj/segment-anything-slides)



# Arch

![Segment Anything Model (SAM) overview](/Users/lyk/Pictures/HexoPics/Machine Learning/Segment Anything/Segment Anything Model (SAM) overview.png)

A heavyweight image encoder outputs an image embedding that can then be efficiently queried by a variety of input prompts to produce object masks at amortized real-time speed. For ambiguous prompts corresponding to more than one object, SAM can output multiple valid masks and associated confidence scores.

## Image Encoder

![image-20231229191214584](/Users/lyk/Library/Application Support/typora-user-images/image-20231229191214584.png)

![image-20231229191421015](/Users/lyk/Library/Application Support/typora-user-images/image-20231229191421015.png)

## Prompt Encoder

> Prompt encoder. We consider two sets of prompts: sparse (points, boxes, text) and dense (masks). We represent points and boxes by positional encodings summed with learned embeddings for each prompt type and free-form text with an off-the-shelf text encoder from CLIP. Dense prompts (i.e., masks) are embedded using convolutions and summed element-wise with the image embedding.
>
> ...
>
> Prompt encoder. Sparse prompts are mapped to 256-dimensional vectorial embeddings as follows. A point is represented as the sum of a positional encoding of the point’s location and one of two learned embeddings that indicate if the point is either in the foreground or background. A box is represented by an embedding pair: (1) the posi- tional encoding of its top-left corner summed with a learned embedding representing “top-left corner” and (2) the same structure but using a learned embedding indicating “bottom- right corner”. Finally, to represent free-form text we use the text encoder from CLIP (any text encoder is possible in general).
>
> Dense prompts (*i.e*., masks) have a spatial correspondence with the image. We input masks at a 4× lower res- olution than the input image, then downscale an additional 4× using two 2×2, stride-2 convolutions with output chan- nels 4 and 16, respectively. A final 1×1 convolution maps the channel dimension to 256. Each layer is separated by GELU activations and layer normalization. The mask and image embedding are then added element-wise. If there is no mask prompt, a learned embedding representing “no mask” is added to each image embedding location.

* **Prompt encoder**: we consider two sets of prompts:
  1. *sparse* (points, boxes, text)
  2. *dense* (masks)
* For points:  point is represented as the sum of a positional encoding of the point’s location and one of two learned embeddings that indicate if the point is either in the foreground or background.
* For boxes: A box is represented by an embedding pair: 
  1. the positional encoding of its <u>top-left corner</u> summed with a learned embedding representing “top-left corner” and
  2. the same structure but using a learned embedding indicating “<u>bottom- right corne</u>r”. 
* For text: CLIP
* For masks: 
  1. A mask is downscaled.
  2. If the mask is not specified, a  “no mask” is added to the image embedding.

## Mask Decoder

> Mask decoder. The mask decoder efficiently maps the im- age embedding, prompt embeddings, and an output token to a mask. This design, inspired by [14, 20], employs a modification of a **Transformer** decoder block [103] followed by a dynamic mask prediction head. 
>
> Our modified decoder block uses **prompt self-attention** and **cross-attention in two directions (prompt-to-image embedding and vice-versa)** to update *all* embeddings. After running two blocks, we up-sample the image embedding and an MLP maps the output token to a dynamic linear classifier, which then computes the mask foreground probability at each image location.

![image-20231229192342894](/Users/lyk/Library/Application Support/typora-user-images/image-20231229192342894.png)

The prompt decoder and mask decoder are both fast so that they can be used within browsers.

![Details of the lightweight mask decoder.](/Users/lyk/Library/Application Support/typora-user-images/image-20231228003812040.png)



A two-layer decoder updates both the image embedding and prompt tokens via cross-attention. Then the image embed- ding is upscaled, from which the updated output tokens are used to dynamically predict masks. (Not illustrated for figure clarity: At every attention layer, positional encodings are added to the image embedding, and the entire original prompt token (including position encoding) is re-added to the token queries and keys.)



![image-20231228011053768](/Users/lyk/Library/Application Support/typora-user-images/image-20231228011053768.png)

### IoU

IoU (Intersection over Union)

![image-20231229193218108](/Users/lyk/Library/Application Support/typora-user-images/image-20231229193218108.png)

![img](https://assets-global.website-files.com/5d7b77b063a9066d83e1209c/647a0e1b55ad60f00d6e0604_IoU%20comparative%20performance.webp)

[-->Image source](https://www.v7labs.com/blog/intersection-over-union-guide)

## Losses and training

> Losses and training. We supervise mask prediction with the linear combination of focal loss [65] and dice loss [73] used in [14]. We train for the promptable segmentation task using a mixture of geometric prompts (for text prompts see §7.5). Following [92, 37], we simulate an interactive setup by randomly sampling prompts in 11 rounds per mask, al- lowing SAM to integrate seamlessly into our data engine.

* focal loss
* dice loss



# Dataset

> Data engine (§4). To achieve strong generalization to new data distributions, we found it necessary to train SAM on a large and diverse set of masks, beyond any segmenta- tion dataset that already exists. While a typical approach for foundation models is to obtain data online [82], masks are not naturally abundant and thus we need an alternative strategy. Our solution is to build a “data engine”, *i.e*., we co-develop our model with model-in-the-loop dataset an- notation (see Fig. 1c). Our data engine has three stages: *assisted-manual*, *semi-automatic*, and *fully automatic*. In the first stage, SAM assists annotators in annotating masks, similar to a classic interactive segmentation setup. In the second stage, SAM can automatically generate masks for a subset of objects by prompting it with likely object lo- cations and annotators focus on annotating the remaining objects, helping increase mask diversity. In the final stage, we prompt SAM with a regular grid of foreground points, yielding on average ∼100 high-quality masks per image.
>
> ...
>
> Assisted-manual stage. In the first stage, resembling clas- sic interactive segmentation, a team of professional annota- tors labeled masks by clicking foreground / background ob- ject points using a browser-based interactive segmentation tool powered by SAM. Masks could be refined using pixel- precise “brush” and “eraser” tools. Our model-assisted an- notation runs in real-time directly inside a browser (using precomputed image embeddings) enabling a truly interac- tive experience. We did not impose semantic constraints for labeling objects, and annotators freely labeled both “stuff” and “things” [1]. We suggested annotators label objects they could name or describe, but did not collect these names or descriptions. Annotators were asked to label objects in order of prominence and were encouraged to proceed to the next image once a mask took over 30 seconds to annotate.
>
> Semi-automatic stage. In this stage, we aimed to increase the *diversity* of masks in order to improve our model’s ability to segment anything. **To focus annotators on less prominent objects, we first automatically detected confident masks. Then we presented annotators with images prefilled with these masks and asked them to annotate any additional unannotated objects.** To detect confident masks, we trained a bounding box detector [84] on all first stage masks using a generic “object” category. During this stage we collected an additional 5.9M masks in 180k images (for a total of 10.2M masks). As in the first stage, we periodically retrained our model on newly collected data (5 times). Average annota- tion time per mask went back up to 34 seconds (excluding the automatic masks) as these objects were more challeng- ing to label. The average number of masks per image went from 44 to 72 masks (including the automatic masks).
>
> Fully automatic stage. In the final stage, annotation was *<u>fully automatic</u>*. This was feasible due to two major en- hancements to our model. First, at the start of this stage, we had collected enough masks to greatly improve the model, including the diverse masks from the previous stage. Second, by this stage <u>we had developed the ambiguity-aware model, which allowed us to predict valid masks even in ambiguous cases</u>. **Specifically, we prompted the model with a 32×32 regular grid of points and for each point predicted a set of masks that may correspond to valid objects.** <u>With the ambiguity-aware model, if a point lies on a part or sub-part, our model will return the subpart, part, and whole object.</u> The IoU prediction module of our model is used to se- lect *confident* masks; moreover, we identified and selected only *stable* masks (we consider a mask stable if threshold- ing the probability map at 0.5 − δ and 0.5 + δ results in similar masks). **Finally, after selecting the confident and stable masks, we applied non-maximal suppression (NMS) to filter duplicates.** To further improve the quality of smaller masks, we also processed multiple overlapping zoomed-in image crops. For further details of this stage, see §B. We applied fully automatic mask generation to all 11M images in our dataset, producing a total of 1.1B high-quality masks. We describe and analyze the resulting dataset, SA-1B, n ext.

![image-20231228012412104](/Users/lyk/Library/Application Support/typora-user-images/image-20231228012412104.png)

## Non-Maximal Suppression (NMS) 

