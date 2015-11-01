% Synthetic face patterns generator. Many processing operators are applied
% to manually cropped facial images and, for each obtained image, many rotation replicas
% are computed.
% At the end of this script 3 structures will be created:
% OriginalImagesDatabase:  structure with original, manually cropped facial images
% ProcessedImagesDatabase: structure with processed images.
% FaceDetectionDatabase:   structure with rotated replica of processed images
% 
% Example:
% If "OriginalImagesDatabase" has 2 facial images manually cropped and 10 processing operations are performed, 
% "ProcessedImagesDatabase" will have 2x10=20 facial images.
% If 15 angles of rotation are applied, "FaceDetectionDatabase" will have 15x20=300 facial images.
% In this way the number of facial patterns is artificially incremented.

clc;clear;close all;
% Read original facial images that have been manually cropped.
counter = 1;

I = imread('original_image1.bmp');
if ndims(I)==3
    I = rgb2gray(I);
end
OriginalImagesDatabase{counter} = I;
counter = counter+1;

I = imread('original_image2.bmp');
if ndims(I)==3
    I = rgb2gray(I);
end
OriginalImagesDatabase{counter} = I;
counter = counter+1;
% Now "OriginalImagesDatabase" is a structure with original facial images, manually cropped.


% For each original facial images, many processing operators are applied.
% "OriginalImagesDatabase" is scanned and each image is processed.
counter = 1;
for scan_original=1:length(OriginalImagesDatabase)
    I = OriginalImagesDatabase{scan_original};
    % Original image
    ProcessedImagesDatabase{counter} = I;
    counter = counter+1;
    % Flip image left to right
    Imod = fliplr(I);
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Histogram equalization
    Imod = histeq(I);
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Apply filter #1
    myfilter = [0 1/2 1/2];
    Imod = uint8(conv2(double(I),myfilter,'same'));
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Apply filter #2
    myfilter = [1/2 1/2 0];
    Imod = uint8(conv2(double(I),myfilter,'same'));
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Apply filter #3
    myfilter = [0; 1/2; 1/2];
    Imod = uint8(conv2(double(I),myfilter,'same'));
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Apply filter #4
    myfilter = [1/2; 1/2; 0];
    Imod = uint8(conv2(double(I),myfilter,'same'));
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Apply filter #5
    myfilter = [1/3; 1/3; 1/3];
    Imod = uint8(conv2(double(I),myfilter,'same'));
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Apply filter #6
    myfilter = [1/3 1/3 1/3];
    Imod = uint8(conv2(double(I),myfilter,'same'));
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Apply filter #7
    myfilter = ones(3,3);
    myfilter = myfilter/sum(myfilter(:));
    Imod = uint8(conv2(double(I),myfilter,'same'));
    ProcessedImagesDatabase{counter} = Imod;
    counter = counter+1;
    % Other processing operations are possible such as gaussian filtering, ...
end


% Now for each of the previous processed artificial image, several images are obtained simply by rotation.
counter = 1;
FaceDetectionDatabase = [];
Ldb = length(ProcessedImagesDatabase);
for scandb=1:Ldb
    img = ProcessedImagesDatabase{scandb};
    for myangle=-17.5:2.5:+17.5
        img_rot = imrotate(img,myangle,'bilinear','crop');
        FaceDetectionDatabase{counter} = img_rot;
        counter = counter+1;
    end
end
% Now "FaceDetectionDatabase" is a structure with original and synthetic facial images.
% If you want to visualize an image just type
% imshow(FaceDetectionDatabase{12})
% to visualize image no.12, ...
% If you want to write this image on disk just use "imwrite" Matlab command.
% With this simple script facial images are incremented by a factor of 150:
% 10 processing operations x 15 angles of rotation.
% There are 15 angles because in [-17.5:2.5:17.5] vector there are exactly 15 elements.




