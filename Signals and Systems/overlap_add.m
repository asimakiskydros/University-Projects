function res = overlap_add (x, h)
    M = length(h);
    P = length(x);

    %create empty column vector y
    %the stitched partial convolutions will be stored here
    y(1 : P + M - 1) = 0;
    y = transpose(y);

    %choose N, L so N is an integer power of 2
    N = 4 * 2^ceil(log2(M));
    L = N - M + 1;

    %begin the partial convolution of y and h
    %the cyclic convolution method employed here is easier to implement
    %it works as we know that F{x conv h} = F{x} times F{h}
    %therefore x conv h = F^-1{F{x} times F{h}}
    H = fft(h, N);
    step = 0;
    while step + L <= P
        y(step + (1:N)) = y(step + (1:N)) + ifft(fft(x(step + (1:L)), N) .* H); 
        step = step + L;
    end

    %return the resulting column vector
    res = y;