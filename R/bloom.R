#' @useDynLib bloom
#' @import Rcpp
loadModule("Bloom", TRUE)

#' Bloom filter
#'
#' Create a new bloom filter, or load a bloom filter from a pre-existing file.
#' @param capacity the approximate expected capacity
#' @param error_rate the desired error rate
#' @param filename the location to store the filter
#' @param exists if the filter exists, load the new filter from a pre-existing file, otherwise
#' create a new filer.
#' @details The filter has the following methods available
#' \describe{
#'   \item{\code{add}}{Add a new item to the bloom filter, each item should be assigned a monotonically increasing id}
#'   \item{\code{contains}}{Check if a given item is contained within the bloom filter}
#'   \item{\code{remove}}{Remove a given item from the filter, the id should match the id given when the item was added}
#' }
#' @export
#' @examples
#' library(bloom)
#' bloom <- bloom(capacity = 1000, error_rate = .05, filename = "/tmp/bloom.bin")
#' bloom$add("foo", 2)
#' bloom$contains("bar")
#' bloom$contains("foo")
#' bloom$remove("foo", 2)
#' bloom$contains("foo")
#' bloom$add("foo", 2)
#' rm(bloom)
#' bloom <- bloom(capacity = 1000, error_rate = .05, filename = "/tmp/bloom.bin", exists = TRUE)
#' bloom$contains("foo")
bloom <- function(
  capacity = 1000,
  error_rate = 0.05,
  filename = tempfile(fileext=".bin"),
  exists = file.exists(filename)
  ) {
  new(bloom::Bloom, capacity, error_rate, filename, exists)
}
