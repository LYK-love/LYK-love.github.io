---
title: VQGAN
tags:
---

Source:

1. [Taming Transformers for High-Resolution Image Synthesis (VQ-GAN)](https://arxiv.org/pdf/2012.09841.pdf)
2. [Pytorch implementation of VQ-GAN ](https://github.com/dome272/VQGAN-pytorch)
3. Youtube: [VQ-GAN | Paper Explanation](https://youtu.be/wcqLFDXaDO8?si=G1_G_B4jiRw0csnp)
4. Youtube: [VQ-GAN | PyTorch Implementation](https://youtu.be/_Br5WRwUz_U?si=UY9xziU4ynVW9wYY)
5. [VAE]()
6. [Neural Discrete Representation Learning (VQ-VAE)](https://arxiv.org/pdf/1711.00937.pdf)

https://compvis.github.io/taming-transformers/



VAE:  [https://towardsdatascience.com/unders...](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbFhJbWV1OU9HRF82Znh0SGc1bXVKeEttaUJVUXxBQ3Jtc0tseEh5b1hob1JpVE5sZXJJdDdzbW1LSUh3VkYtV1FabnoyYzNyMW1reTdlVlI1cHlRa1ljcGZJT3dGRWlvc1hITVNRT1J1Z0szTmtFdldEOUcyYkFfNHhoejltNW9qb04zZ21XZ0EzNVZJeDdDZW5sSQ&q=https%3A%2F%2Ftowardsdatascience.com%2Funderstanding-variational-autoencoders-vaes-f70510919f73&v=wcqLFDXaDO8) •  VQVAE: [https://arxiv.org/pdf/1711.00937.pdf](https://www.youtube.com/redirect?event=video_description&redir_token=QUFFLUhqbUxrMTZYc01lV0FHcUswT3d6Q0tfY3M2SVJtUXxBQ3Jtc0trQ2h0WlU5aV9qdDlaZzRLMEhfZTU0XzdxTFdIUENkSzhUY3c5VUFXeFdHblp3S0NpZ3FLREJtdmtTcTlPQTVyRHRUdjQ4eTgwZm5ocFQydmdXbjBoakVEWnBXUjhHTE55S2hST3M2RlNvbHJUeEloZw&q=https%3A%2F%2Farxiv.org%2Fpdf%2F1711.00937.pdf&v=wcqLFDXaDO8)



VQVAE + GAN



VAE: continuous latent space ---> VQVAE: **discrete** latent space

Unlike VAEs with continuous latent spaces, VQVAEs use a discrete space  by having a codebook containing a large number of continuous vectors.  The VQVAE encoding process maps an image to a continuous space then for  each spatial location changes each vector to the closest one in the  codebook.

# VAVAE



![image-20240113224207795](/Users/lyk/Library/Application Support/typora-user-images/image-20240113224207795.png)

