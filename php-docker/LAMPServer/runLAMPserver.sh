#!/bin/bash

docker stop $(docker ps -a -q) ; docker rm $(docker ps -a -q)
docker build -t lamp_server .
docker run -t -i -p 8876:8876 -p 54321:54321 --network=host lamp_server
