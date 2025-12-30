# .devcontainer/Dockerfile
FROM ubuntu:22.04

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
    gcc \
    gdb \
    strace \
    sudo \
    make \
    && rm -rf /var/lib/apt/lists/*

ENV LD_LIBRARY_PATH=/workspace/project/build/lib:${LD_LIBRARY_PATH}

COPY settings/.vimrc /root/.vimrc

WORKDIR /workspace