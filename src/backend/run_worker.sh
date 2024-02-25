#/bin/bash

celery -A src.background.celery_app worker --loglevel=info
