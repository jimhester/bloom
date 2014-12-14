<!-- README.md is generated from README.Rmd. Please edit that file -->
bloom
=====

Scaling, counting Bloom filter for R using Rcpp bindings for [dablooms](https://github.com/bitly/dablooms/).

Note the dablooms implementation requires an additional metadata id for insertions and deletions. This id is a monotonically increasing integer which is used to determine which scaling filter the item should be added or removed from.

### Example usage

``` r
library(bloom)
bloom <- bloom(capacity = 1000, error_rate = .05, filename = "/tmp/bloom.bin")
bloom$add("foo", 2)
#> [1] 1
bloom$contains("bar")
#> [1] FALSE
bloom$contains("foo")
#> [1] TRUE
bloom$remove("foo", 2)
#> [1] 1
bloom$contains("foo")
#> [1] TRUE
bloom$add("foo", 2)
#> [1] 1
rm(bloom)
bloom <- bloom(capacity = 1000, error_rate = .05, filename = "/tmp/bloom.bin", exists = TRUE)
bloom$contains("foo")
#> [1] TRUE
```
