docker run -it --rm \
  --user $(id -u):$(id -g) \
  -v "$(pwd)":/timelib -w /timelib \
  timelib bash -login