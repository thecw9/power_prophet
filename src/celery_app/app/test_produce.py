from app.celery_tasks import pull_oil_chromatography

pull_oil_chromatography.delay()
