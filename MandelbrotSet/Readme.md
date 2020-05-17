# Mandelbrot interactive fractal set using SFML 2.5

Most popular fractal revisited with C++ and SFML 2.5

![EXAMPLE2](ex2.JPG)
![EXAMPLE1](ex1.JPG)


## Installation

Follow the tutorial at [SFML](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) to install SFML.

## Usage

W|A|S|D to move around
UP|DOWN to increase or decrease iterations
Mouse wheel to zoom in and out
R to restart
E to save image

To chage colors edit
```c++

static const std::vector<sf::Color> colors{
    {0,0,0},
    {213,67,31},
    {251,255,121},
    {62,123,89},
    {43,30,118},
    {0,55,247},
};

```
![EXAMPLE3](ex3.JPG)

## License
[MIT](https://choosealicense.com/licenses/mit/)