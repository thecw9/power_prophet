import atexit

import sounddevice as sd


# list all available devices and their info
def list_devices():
    devices = sd.query_devices()

    devices = [device for device in devices if device["max_input_channels"] > 0]

    for device in devices:
        print(device)


class Microphone:
    def __init__(self, device, channels, sample_rate=48000):
        self.device = device
        self.channels = channels
        self.sample_rate = sample_rate
        self.stream = sd.InputStream(
            device=self.device,
            channels=self.channels,
            samplerate=self.sample_rate,
        )
        self.stream.start()
        atexit.register(self.close)

    def list_devices(self):
        print(sd.query_devices())

    def read(self, num_samples=48000):
        data = self.stream.read(num_samples)
        return data[0]

    def close(self):
        print("Closing microphone stream")
        self.stream.stop()
        self.stream.close()


if __name__ == "__main__":
    list_devices()
    # mic = Microphone(device=0, channels=1)
    mic = Microphone(device="USB_MIC", channels=1)
    for i in range(10):
        data = mic.read()
        print(data)
