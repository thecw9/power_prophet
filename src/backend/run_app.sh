#/bin/bash

uvicorn src.main:app --reload --host 0.0.0.0 --port 8000 --log-config uvicorn_config.json
