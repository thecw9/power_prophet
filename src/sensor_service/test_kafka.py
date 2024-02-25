from kafka import KafkaProducer, KafkaConsumer

# Kafka 服务器的地址
bootstrap_servers = "localhost:9094"
# 主题名称
topic_name = "test_topic"

# 生产者发送消息
producer = KafkaProducer(bootstrap_servers=bootstrap_servers)
producer.send(topic_name, value=b"Hello, Kafka!")
producer.flush()

# 消费者接收消息
consumer = KafkaConsumer(
    topic_name,
    bootstrap_servers=bootstrap_servers,
    auto_offset_reset="earliest",
    enable_auto_commit=True,
)

messages = consumer.poll(timeout_ms=1000, max_records=1)
for tp, msgs in messages.items():
    for msg in msgs:
        print(f"Received message: {msg.value.decode('utf-8')}")
