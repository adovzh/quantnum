# Hello, world!
#
# This is an example function named 'hello'
# which prints 'Hello, world!'.
#
# You can learn more about package authoring with RStudio at:
#
#   http://r-pkgs.had.co.nz/
#
# Some useful keyboard shortcuts for package authoring:
#
#   Build and Reload Package:  'Cmd + Shift + B'
#   Check Package:             'Cmd + Shift + E'
#   Test Package:              'Cmd + Shift + T'

testLinear <- function() {
    library(tibble)
    library(ggplot2)

    x <- 1:5
    y <- c(2, 3, 5, 10, 7)
    ds <- tibble(x = x, y = y)

    ix <- seq(1, 5, 0.01)
    iy <- lininterp(x, y, ix)
    ids <- tibble(x = ix, y = iy)

    ggplot() + geom_line(data = ids, aes(x = ix, y = iy)) +
        geom_point(data = ds, aes(x = x, y = y))
}
