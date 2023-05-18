# syntax=docker/dockerfile:1

# Using CUDA 11 instead of 12 because of
# https://github.com/ROCm-Developer-Tools/hipamd/issues/73
FROM nvidia/cuda:11.8.0-devel-ubuntu22.04

# Install dev tools
# bazel:      building
# git:        version control
# libgl-dev:  HIP dependency (should probably fetch this with bazel eventually)
# zsh:        convenience in terminal
RUN apt-get update && \
    apt-get install -y apt-transport-https curl gnupg && \
    curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor -o /usr/share/keyrings/bazel-archive-keyring.gpg && \
    echo 'deb [signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8' | tee /etc/apt/sources.list.d/bazel.list && \
    apt-get update && \
    apt-get install -y \
      bazel \
      git \
      libgl-dev \
      zsh

# Maybe:
# upgrade to GCC 12
# apt-get install -y gcc-12 g++-12
# update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 60 --slave /usr/bin/g++ g++ /usr/bin/g++-12
