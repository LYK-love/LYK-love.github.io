---
title: LLM and World Models
tags:
---



A model-based agent comprises a policy and a world model, where the policy is optimized with respect to the world model. This modular design can result in more effective control over “model-free” counterparts, allowing humans to alter the agent’s behavior both:

1. explicitly, by directly updating its policies (e.g., through reinforcement or imitation learning), or
2. **implicitly**, by **adapting its world model** (which subsequently also changes the policies).



being able to incorporate human language-based supervision

```
docker run  --network=host -v open-webui:/app/backend/data -e OLLAMA_API_BASE_URL=http://127.0.0.1:11434/api --name open-webui --restart always ghcr.io/open-webui/open-webui:main
```

