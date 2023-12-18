---
title: Common Probability Distributions
tags:
---



# Normal Distribution

$$
p(x) = \frac{1}{\sqrt{2 \pi \sigma^2}} \exp\left(-\frac{1}{2 \sigma^2} (x - \mu)^2\right).
$$

```python
import torch
def normal(x, mu, sigma):
    left_term = 1 / torch.sqrt(torch.tensor(2 * torch.pi * (sigma ** 2)))
    right_term = torch.exp( (-1)/(2 * (sigma**2)) * (x-mu)**2)
    return left_term * right_term
```



Visualization:

```python
import torch
import matplotlib.pyplot as plt
# Visualization
x = torch.arange(-7, 7, 0.01)

# Mean and standard deviation pairs
params = [(0, 1), (0, 2), (3, 1)]

plt.figure(figsize=(10, 6))

for mu, sigma in params:
    y = normal(x, mu, sigma)
    plt.plot(x.numpy(), y.numpy(), label=f'N({mu}, {sigma**2})')

plt.title('Normal Distributions')
plt.xlabel('x')
plt.ylabel('Probability Density')
plt.legend()
plt.show()
```



![myplot](/Users/lyk/Documents/cache/myplot.png)

