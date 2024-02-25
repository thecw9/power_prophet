#!/bin/bash

# Server info
SERVER_HOST=10.159.1.46
SERVER_USER=thecw

REMOTE_PATH=/home/$SERVER_USER/Projects
LOCAL_PATH=$(pwd)

# create remote directory if it doesn't exist
ssh $SERVER_USER@$SERVER_HOST "mkdir -p $REMOTE_PATH"

# Copy files to the server
rsync -avz --exclude-from './deploy_exclude.txt' $LOCAL_PATH $SERVER_USER@$SERVER_HOST:$REMOTE_PATH
