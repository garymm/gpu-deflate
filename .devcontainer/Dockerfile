# syntax=docker/dockerfile:1

FROM nvidia/cuda:12.1.1-devel-ubuntu22.04
# FROM ubuntu:22.04

# TODO: make this work on arm64
# see https://docs.docker.com/engine/reference/builder/#automatic-platform-args-in-the-global-scope
# if [ "$TARGETARCH" = "amd64" ]; then CUDA_ARCH=x86_64; elif [ "$TARGETARCH" = "arm64" ]; then CUDA_ARCH=sbsa; else CUDA_ARCH=x86_64; fi \

# Install parts of CUDA
# CUDA docs say I need linux-headers too, but that's tricky inside docker.
# RUN CUDA_ARCH=x86_64; \
#     apt-get update && \
#     apt-get install -y apt-transport-https curl gnupg && \
#     curl -fsSL https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/${CUDA_ARCH}/cuda-ubuntu2204-keyring.gpg | gpg --dearmor -o /etc/apt/trusted.gpg.d/cuda-archive-keyring.gpg && \
#     echo "deb [signed-by=/etc/apt/trusted.gpg.d/cuda-archive-keyring.gpg] https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/${CUDA_ARCH}/ /" | tee /etc/apt/sources.list.d/cuda-ubuntu2204-${CUDA_ARCH}.list

# Install HIP
    # curl -fsSL https://repo.radeon.com/rocm/rocm.gpg.key | gpg --dearmor -o /etc/apt/trusted.gpg.d/rocm-keyring.gpg && \
    # echo 'deb [signed-by=/etc/apt/trusted.gpg.d/rocm-keyring.gpg] https://repo.radeon.com/rocm/apt/5.5 jammy main' | tee /etc/apt/sources.list.d/amdgpu.list && \
    # apt-get update && apt-get install -y hip-dev hipify-clang

# Install Bazel and GCC
RUN apt-get update && \
    apt-get install -y apt-transport-https curl gnupg && \
    curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor -o /usr/share/keyrings/bazel-archive-keyring.gpg && \
    echo 'deb [signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8' | tee /etc/apt/sources.list.d/bazel.list && \
    PPA_KEY_FINGERPRINT=$(curl "https://launchpad.net/api/1.0/~ubuntu-toolchain-r/+archive/test" \
        | sed -En 's/.*"signing_key_fingerprint": "([^"]*)".*/\1/ p') && \
    curl "https://keyserver.ubuntu.com/pks/lookup?op=get&options=mr&exact=on&search=0x${PPA_KEY_FINGERPRINT}" \
        | gpg -q --dearmor -o /usr/share/keyrings/ubuntu-toolchain-r-test.gpg && \
    echo 'deb [signed-by=/usr/share/keyrings/ubuntu-toolchain-r-test.gpg] https://ppa.launchpadcontent.net/ubuntu-toolchain-r/test/ubuntu/ jammy main' > /etc/apt/sources.list.d/ubuntu-toolchain-r-test.list && \
    apt-get update && \
    apt-get install -y bazel gcc-13 g++-13 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 60 --slave /usr/bin/g++ g++ /usr/bin/g++-13
