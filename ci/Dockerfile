FROM ubuntu:22.04

RUN apt-get update                                      && \
    apt-get install -y wget \
    lsb-release \
    software-properties-common \
    gnupg                            && \
    bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" && \
    apt-get install -y                                     \
    git                                                    \
    ninja-build                                            \
    cmake                                                  \
    clang-17                                               \
    libgtest-dev
