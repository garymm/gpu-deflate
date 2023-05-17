# syntax=docker/dockerfile:1

FROM nvidia/cuda:12.1.1-devel-ubuntu22.04

# Install dev tools
RUN apt-get update && \
    apt-get install -y apt-transport-https curl gnupg && \
    curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor -o /usr/share/keyrings/bazel-archive-keyring.gpg && \
    echo 'deb [signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8' | tee /etc/apt/sources.list.d/bazel.list && \
    apt-get update && \
    apt-get install -y \
      bazel \
      git \
      zsh
