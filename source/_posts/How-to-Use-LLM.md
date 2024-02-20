---
title: How to Use LLM
date: 2024-02-20 00:09:54
categories:
- Software Engineering
tags: Machine Learning
---

How to use LLMs (Large Language Models), including how to host them, how to add a frontend to them and others.

<!--more-->

# Ollama

* [Ollama](https://ollama.com/)
* [Ollama github repo](https://github.com/ollama/ollama?tab=readme-ov-file)

## Installation

My system configuration is:

* Ubuntu 22.04
* ISA: x86_64
* GPUs: two NVIDIA 1080Tis

### Install on bare-metal

```sh
curl -fsSL https://ollama.com/install.sh | sh
```

[Manual install instructions](https://github.com/jmorganca/ollama/blob/main/docs/linux.md)

### Install with Docker

First, you need to install the [NVIDIA Container Toolkit](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html#installation). Since I use Ubuntu, I choose the `apt` installation method.

1. Configure the production repository:

   ```sh
   curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
     && curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
       sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
       sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
   ```

   Optionally, configure the repository to use experimental packages:

   ```sh
   sed -i -e '/experimental/ s/^#//g' /etc/apt/sources.list.d/nvidia-container-toolkit.list
   ```

2. Update the packages list from the repository:

   ```sh
   sudo apt-get update
   ```

3. Install the NVIDIA Container Toolkit packages:

   ```sh
   sudo apt-get install -y nvidia-container-toolkit
   ```

4. Restart the Docker daemon:

   ```
   sudo systemctl restart docker
   ```



Next, Check if your docker service is healthy:

```sh
sudo systemctl status docker
```



If it shows error like:

```
Failed to start Docker Application Container Engine.
```

You need to reboot the computer.



FInally, you can run the container:

```sh
docker run -d --gpus=all -v ollama:/root/.ollama -p 11434:11434 --name ollama ollama/ollama
```

## Run the model

To run and chat with [Llama 2](https://ollama.com/library/llama2):



If you install ollama on bare-metal:

```sh
ollama run llama2
```

If you install ollama via docker

```sh
docker exec -it ollama ollama run llama2
```



You can switch to other models. Ollama supports a list of open-source models available on the [Ollama library](https://ollama.ai/library).

Here are some example open-source models that can be downloaded:

| Model              | Parameters | Size  | Download                       |
| ------------------ | ---------- | ----- | ------------------------------ |
| Llama 2            | 7B         | 3.8GB | `ollama run llama2`            |
| Mistral            | 7B         | 4.1GB | `ollama run mistral`           |
| Dolphin Phi        | 2.7B       | 1.6GB | `ollama run dolphin-phi`       |
| Phi-2              | 2.7B       | 1.7GB | `ollama run phi`               |
| Neural Chat        | 7B         | 4.1GB | `ollama run neural-chat`       |
| Starling           | 7B         | 4.1GB | `ollama run starling-lm`       |
| Code Llama         | 7B         | 3.8GB | `ollama run codellama`         |
| Llama 2 Uncensored | 7B         | 3.8GB | `ollama run llama2-uncensored` |
| Llama 2 13B        | 13B        | 7.3GB | `ollama run llama2:13b`        |
| Llama 2 70B        | 70B        | 39GB  | `ollama run llama2:70b`        |
| Orca Mini          | 3B         | 1.9GB | `ollama run orca-mini`         |
| Vicuna             | 7B         | 3.8GB | `ollama run vicuna`            |
| LLaVA              | 7B         | 4.5GB | `ollama run llava`             |

> Note: You should have at least 8 GB of RAM available to  run the 7B models, 16 GB to run the 13B models, and 32 GB to run the 33B models.

## Customize a model

### Import from GGUF

**GGUF (GPT-Generated Unified Format)**, introduced as a successor to GGML (GPT-Generated Model Language), is a file format used for storing models for inference, especially in the  context of language models like GPT (Generative Pre-trained  Transformer). 



Ollama supports importing GGUF models in the Modelfile:

1. Create a file named `Modelfile`, with a `FROM` instruction with the local filepath to the model you want to import.

   ```sh
   FROM ./vicuna-33b.Q4_0.gguf
   ```

2. Create the model in Ollama

   ```sh
   ollama create example -f Modelfile    
   ```

3. Run the model

   ```sh
   ollama run example
   ```

### Import from PyTorch or Safetensors

See the [guide](https://github.com/ollama/ollama/blob/main/docs/import.md) on importing models for more information.

### Customize a prompt

Models from the Ollama library can be customized with a prompt. For example, to customize the `llama2` model:

```
ollama pull llama2
```

​    

Create a `Modelfile`:

```
FROM llama2

# set the temperature to 1 [higher is more creative, lower is more coherent]
PARAMETER temperature 1

# set the system message
SYSTEM """
You are Mario from Super Mario Bros. Answer as Mario, the assistant, only.
"""
```

​    

Next, create and run the model:

```
ollama create mario -f ./Modelfile
ollama run mario
>>> hi
Hello! It's your friend Mario.
```

​    

For more examples, see the [examples](https://github.com/ollama/ollama/blob/main/examples) directory. For more information on working with a Modelfile, see the [Modelfile](https://github.com/ollama/ollama/blob/main/docs/modelfile.md) documentation.

# Open-webui

* [Github: open-webui](https://github.com/open-webui/open-webui)
* [Open WebUI Community](https://openwebui.com/)

Ollama works at terminal, we can install a frontend for it. We choose open-webui since its fast and has no bug.



![Open WebUI Demo](https://github.com/open-webui/open-webui/raw/main/demo.gif)

## Installation

1. Install Ollama, by default it listens to port 11434.

2. Run

   ```sh
   docker run -d --network=host -v open-webui:/app/backend/data -e OLLAMA_API_BASE_URL=http://127.0.0.1:11434/api --name open-webui --restart always ghcr.io/open-webui/open-webui:main
   ```

   Source: [Open WebUI: Server Connection Error](https://github.com/open-webui/open-webui/blob/main/TROUBLESHOOTING.md)

3. Then visit http://localhost:8080

# BionicGPT

[BionicGPT](https://bionic-gpt.com/)

[BionicGPT github repo](https://github.com/bionic-gpt/bionic-gpt)

[Install BionicGPT via `docker compose`](https://bionic-gpt.com/docs/running-locally/gpu-setup-ollama/)

The easiest way to get running with BionicGPT is with our `docker-compose.yml` file. You'll need [Docker](https://docs.docker.com/engine/install/) installed on your machine.

```sh
mkdir BionicGPT
cd BionicGPT
curl -O https://raw.githubusercontent.com/bionic-gpt/bionic-gpt/main/docker-compose/docker-compose.yml
docker compose up -d
```

You must have access to ports `7800` and `7810`.

## Run the User Interface

You can then access the front end from `http://localhost:7800` and you'll be redirected to a registration screen.

The first user to register with **BionicGPT** will become the system administrator.
