<!-- README.md is generated from README.Rmd. Please edit that file -->
bloom
=====

R language bindings for dablooms.

### Example usage

``` r
library(bloom)
bloom <- new(bloom::bloom, 1000, .05, "/tmp/bloom.bin")
bloom$add("foo", 2)
#> [1] TRUE
bloom$check("bar")
#> [1] 0
bloom$check("foo")
#> [1] 1
bloom$remove("foo", 2)
#> [1] TRUE
bloom$check("foo")
#> [1] 0
```
