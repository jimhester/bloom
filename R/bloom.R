loadModule("Bloom", TRUE)

bloom <- function(
  capacity = 1000,
  error_rate = 0.05,
  filename = tempfile(fileext=".bin"),
  exists = file.exists(filename)
  ) {

  new(bloom::Bloom, capacity, error_rate, filename, exists)

}
