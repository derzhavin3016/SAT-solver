FROM ubuntu:22.04

RUN apt-get update                                      && \
    apt-get install -y wget \
    lsb-release \
    software-properties-common \
    gnupg                            && \
    bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" && \
    apt-get install -y                                     \
    git                                                    \
    python3-pip                                            \
    clang-17                                               \
    libgtest-dev                                           \
    unzip && mkdir -p /opt/ninja

RUN wget -P /tmp https://github.com/ninja-build/ninja/releases/download/v1.11.1/ninja-linux.zip && \
    unzip /tmp/ninja-linux.zip -d /opt/ninja/

RUN wget https://github.com/Kitware/CMake/releases/download/v3.28.0-rc3/cmake-3.28.0-rc3-linux-x86_64.tar.gz && \
    tar -xf cmake-3.28.0-rc3-linux-x86_64.tar.gz && \
    mv cmake-3.28.0-rc3-linux-x86_64 /opt/cmake-3.28


ENTRYPOINT ["/bin/bash"]
