function [ mH ] = meanHue( imRGB , reg)
%MEANHUE Summary of this function goes here
%   Detailed explanation goes here

        imHSV = rgb2hsv(imRGB);
        imHue = imHSV(:,:,1);
        mH = mean(imHue(reg));
end

