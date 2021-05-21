FROM ubuntu:focal


RUN apt-get update 
WORKDIR /workspace
ENV DASH_DEBUG_MODE True

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y \
        apt-utils \
        sudo \
        git \
        build-essential \
        cmake \
        python3 \
        python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN set -ex && \
    pip3 install cget==0.1.9 \ 
         dash==1.12.0 \
         dash-bootstrap-components==0.12.2 \
         dash-daq==0.5.0 \
         dash-cytoscape==0.2.0 \
         networkx==2.5.1 \
         numpy==1.20.3


RUN cget install nlohmann/json

EXPOSE 8050