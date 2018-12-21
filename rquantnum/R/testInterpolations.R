library(tibble)
library(ggplot2)
library(dplyr)
library(tidyr)

testInterps <- function(...) {
    args <- as.character(list(...))
    table <- c("all", "linear", "polynomial", "spline")
    args <- sapply(args, function (a) match.arg(a, table))

    x <- 1:5
    y <- c(2, 3, 5, 10, 7)
    ds <- tibble(x = x, y = y)

    ix <- seq(1, 5, 0.01)
    ids <- tibble(x = ix)
    doall <- "all" %in% args

    if (doall || ("linear" %in% args)) {
        iy <- lininterp(x, y, ix)
        ids <- ids %>% mutate(Linear = iy)
    }

    if (doall || ("polynomial" %in% args)) {
        iy <- polyinterp(x, y, 5, ix)
        ids <- ids %>% mutate(Polinomial = iy)
    }

    if (doall || ("spline" %in% args)) {
        iy <- splineinterp(x, y, ix)
        ids <- ids %>% mutate(Spline = iy)
    }

    ids.melted <- ids %>% gather(Method, y, -x)

    ggplot() + geom_line(data = ids.melted, aes(x, y, color = Method)) +
        geom_point(data = ds, aes(x = x, y = y)) +
        ggtitle("Interpolation Methods")
}

testLinear <- function() testInterps("lin")
testPoly <- function() testInterps("poly")
testSpline <- function() testInterps("spline")
testAllInterps <- function() testInterps("all")
