# AsciImage program
This is a small version of a simple program that accepts a image, (and optionally) sizex and sizey as inputs, and returns a string of characteres encoding each pixel with a encoded character. 

This program obviously doesn't aim economical profits, is just a personal projects to learn more about  coding and data manipulation.

### Usage
The usage is very simple, and can be described by the following syntax:

```[executable] [image filename] [sizex] [sizey]```

As described before, is not necessary to especify **sizex** and **sizey**, if one of arguments is passed, then you need to specify both. 

**sizex** and **sizey** is used by the program to make chunks of pixels of the original image (so the arguments just specify the size of this chunks), and makes a arithmetic mean of this pixels and place into a singular pixel. This method is used just to downscale the image, is similar to Blur method and the image lost signifcantly contrast and details using this method. 

Other methods of downscaling probably would improve the image quality. But for simplicity I just wrote that (maybe coming soon other functions).

### Compiling
For compiling just run ```make``` and be happy.

### Errors
Obviously this code has some bugs and errors, one bug that is being solved is a duplicated jpg image printing, any pull requests would be great to compare code and find soulutions.
