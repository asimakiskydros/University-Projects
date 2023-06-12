%get signal data
[signal, Fs] = audioread("Connections.mp3");

%create the low pass filter
%given length of 300 and cutoff frequency of 0.15
lowpass_filter = fir1(300, 0.15);
lowpass_filter = transpose(lowpass_filter);

%deal with each column of the sound signal seperate and then merge them
y = [overlap_add(signal(:,1), lowpass_filter), overlap_add(signal(:,2), lowpass_filter)];

%plotting the starting and final signals
figure(1), clf,
subplot(2,2,1), plot(signal), title("Connections.mp3")
subplot(2,2,2), plot(y, "r"), title("Connections.wav")
subplot(2,2,3), plot(abs(fft(signal))), title("Fourier of Connections.mp3")
subplot(2,2,4), plot(abs(fft(y)), "r"), title("Fourier of Connections.wav")

%export the wav file
audiowrite("Connections.wav", y, Fs);