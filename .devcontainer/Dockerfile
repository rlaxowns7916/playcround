# .devcontainer/Dockerfile
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# 기본 유틸
RUN apt-get update && apt-get install -y \
    ca-certificates \
    curl \
    wget \
    git \
    vim \
    unzip \
    zip \
    net-tools \
    iputils-ping \
    lsb-release \
    bash-completion \
    sudo \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace