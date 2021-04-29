FROM ubuntu:focal


RUN apt-get update 


WORKDIR /root

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

RUN pip3 install cget \ 
         dash \
         dash-bootstrap-components \
         dash-cytoscape \
         networkx \
         numpy

RUN cget install nlohmann/json