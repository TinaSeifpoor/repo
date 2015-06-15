function I_ycbcr = rgb2ycbcr( I_rgb )
%RGB2YCBCR Summary of this function goes here
%   Detailed explanation goes here
% http://stackoverflow.com/questions/17892346/how-to-convert-rgb-yuv-rgb-both-ways
% http://www.equasys.de/colorconversion.html
% JPEG/JFIF YCbCr conversions
% 
%     Y  = R *  0.29900 + G *  0.58700 + B *  0.11400
%     Cb = R * -0.16874 + G * -0.33126 + B *  0.50000 + 128
%     Cr = R *  0.50000 + G * -0.41869 + B * -0.08131 + 128
% 
%     R  = Y +                       + (Cr - 128) *  1.40200
%     G  = Y + (Cb - 128) * -0.34414 + (Cr - 128) * -0.71414
%     B  = Y + (Cb - 128) *  1.77200
R = I_rgb(:,:,1,:);
G = I_rgb(:,:,2,:);
B = I_rgb(:,:,3,:);

Y = R * 0.29900 + G * 0.58700 + B * 0.11400;
Cb = R * -0.16874 + G * -0.33126 + B *  0.50000 + 128;
Cr = R *  0.50000 + G * -0.41869 + B * -0.08131 + 128;
I_ycbcr = cat(3,Y,Cb,Cr);

end

