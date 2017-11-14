clear all
close all

tic

% mex -setup c++
% mex FIRFilter.cpp
% mex IIRFilter.cpp

FS = 44100;
butterfrek_hz=3250;
butterfrek=(butterfrek_hz/(FS/2));
butter_order = 6;
[b,a] = butter(butter_order, butterfrek, 'low');

y_sample = audioread ('Green Day - Longview 90sec.wav');
y_sample = y_sample (1:100000,1);
[y_out] = IIRFilter(y_sample, b, a, butter_order, length(y_sample));

toc