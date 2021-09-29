# iSocket

iSocket is a risk recorder for sleep apnea.
Simply put, this is a way to analyze your risk of sleep apnea from your screaming.
From the physiological principle of snoring, it can be found that almost as long as one can breathe, the phenomenon of snoring occurs. So in fact, we can analyze the physical condition from the state and characteristics of snoring. Snoring has a high probability of causing repeated pauses in breathing, which will cause severe hypoxia in the brain and blood, and then form hypoxemia, which is likely to induce many cardiovascular-related diseases.
And according to statistics, about 100 million people in the world suffer from sleep apnea, but the number of patients in Taiwan can reach as many as one million people. What’s more, the diagnosis rate is only 20%.
This means that there are more people who don't know that they have suffered from sleep apnea. This is why we think it is very important to analyze the modalities and characteristics of daily snoring.
If we can help people to analyze the snoring modalities "without feeling" and use technology to remind us to pay attention to our health, I believe this will help more patients who do not know that they have suffered from sleep apnea can grasp the gold The treatment period.

## Hardware design and parameters

To achieve the effect of analyzing the snoring mode, the first key point is the radio.
I designed three ultra-mini condenser INMP441 microphones to form an array, which can receive sounds over the range of 185 degrees, and we also designed a compensation algorithm that can superimpose these microphones and compensate for details, so that the entire analysis sample can be included. It is more complete, coupled with the shell as a windshield, it can avoid receiving too noisy ambient sound like an electric fan.
So at present, we have good sound effects within one meter.

## AI and algorithm analysis

When the system receives a sound, the first part will first identify whether there is a snoring sound, so what do we do?
We will use Fast Fourier Transform and Wavelet Transform to find the fundamental frequency, frequency centroid, and sound quality of this sound, and use these characteristics as features, and use classification algorithms to classify these features into human voice, environmental sound, speech, or Scream.
Next, we need to use the frequency band and characteristics of this snoring to determine if it is abnormal. I use LSTM with Gaussian anomaly detection algorithm to detect.
We use the database provided by Kaggle for training, our accuracy rate can reach 90%
