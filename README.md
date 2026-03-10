This project uses Clay and comparmentalises the UI into components and layouts,
inspired by Svelte. Components are prefixed with a `c` while layouts are prefixed
with `layout`.

There is also `globals.c` and `globals.h` files that includes data that is shared
between all layouts, components, and the `main.c` file.

```
cmake -S . -B build -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang
cmake --build build
```

#### Library Plans
 - Port Audio (Audio I/O)
 - libsndfile (file and codec handling)
 - KFR or FFTW (signal processing)
 - VST3 SDK or CLAP (plugin hosting)