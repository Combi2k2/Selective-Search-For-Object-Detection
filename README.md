# Selective-Search-For-Object-Detection


### Reason of this repo
I read and reformat the code for my own better comprehension

### Original Project:
http://cs.brown.edu/people/pfelzens/segment/


### Basic idea of the algorithm:
<li> If some pixels is not quite different from the pixels aroound it, so they merge together and become a new region in the result image </li>
<li> The colors of the new regions are randomly generated </li>
<li> They is like masks for regions with same color </li>
<li> Merging some masks is the most naive idea for object detection </li>

### Run project:
Copy the following command to your terminal (but change the arguments INPUT_IMAGE and OUTPUT_IMAGE):

    g++ segment.cpp -o segment
    ./segment 0.5 500 20 INPUT_IMAGE OUTPUT_IMAGE

### The following lines belong to the actual author of this project:
Implementation of the segmentation algorithm described in:

Efficient Graph-Based Image Segmentation
Pedro F. Felzenszwalb and Daniel P. Huttenlocher
International Journal of Computer Vision, 59(2) September 2004.

The program takes a color image (PPM format) and produces a segmentation
with a random color assigned to each region.

1) Type "make" to compile "segment".

2) Run "segment sigma k min input output".

The parameters are: (see the paper for details)

sigma: Used to smooth the input image before segmenting it.
k: Value for the threshold function.
min: Minimum component size enforced by post-processing.
input: Input image.
output: Output image.

Typical parameters are sigma = 0.5, k = 500, min = 20.
Larger values for k result in larger components in the result.



