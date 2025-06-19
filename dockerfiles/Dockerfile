FROM kalilinux/kali-last-release AS deps

RUN  apt-get update \
     && DEBIAN_FRONTEND="noninteractive" apt-get install -y --no-install-recommends --fix-missing \
       ca-certificates \
       curl \
       gdb \
       git \
       gnupg \
       lsb-release \
       zip

RUN  apt-get update \
     && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends --fix-missing \
       graphviz \
       clang \
       doxygen \
       libcurl4-openssl-dev \
       llvm \
       llvm-dev \
       lld \
       python3-dev \
       python3-pip \
       python3-setuptools \
       build-essential \
       cmake \
       libyaml-cpp-dev

ENV  LLVM_CONFIG=llvm-config-16

FROM deps AS aflpp

# Clone and build AFL++
RUN set -ex \
    && cd /usr/local/src \
    && git clone --depth 1 -b v4.10c https://github.com/AFLplusplus/AFLplusplus.git \
    && cd AFLplusplus \
    && make all \
    && make install \
    && set +ex
    
FROM aflpp AS vmf

# Clone, build, install VMF
# TODO temp fix until we update for 5.0.0
RUN set -ex \
    && cd /usr/local/src \
    && git clone https://github.com/draperlaboratory/vadermodularfuzzer.git VaderModularFuzzer\
    && cd VaderModularFuzzer \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make -j \
    && make install \
    && set +ex
    
# Copy VmfExperimental
COPY . /usr/local/src/VmfExperimental

RUN set -ex \
    && cd /usr/local/src/VmfExperimental \
    && mkdir build \
    && cd build \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr/local/src/VaderModularFuzzer/build/vmf_install .. \
    && make -j \
    && make install \
    && set +ex

# Create experimental config file
RUN set -ex \
    && cd /usr/local/src/ \
    && cp VmfExperimental/Radamsa/test/config/experimentalModules.yaml VaderModularFuzzer/build/vmf_install/test/config/experimentalModules.yaml \
    && set +ex

# WORKDIR /usr/local/src/VmfExperimental/build
WORKDIR /usr/local/src/VaderModularFuzzer/build/vmf_install
ENTRYPOINT [ "./bin/vader", "-c", "test/config/experimentalModules.yaml", "-c", "test/haystackSUT/haystack_stdin.yaml" ]
