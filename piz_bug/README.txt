TinyEXR fails to read PIZ-compressed images correctly if they contain large regions of zeros. The output will contain large horizontal strips of zeros.
OpenEXR seems to load the images fine. Tested with mrViewer.

The big input image (broken.exr) is from the Tungsten NFOR denoiser example data set (https://github.com/tunabrain/tungsten/tree/master/src/denoiser).

The folder broken_images contains sereval broken example images that are much simpler. The bug seems to happen with 3-channel RGB images as well as scalar images.