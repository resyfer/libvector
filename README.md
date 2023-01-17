# libvector

A vector library for C. Easy to use as well as takes in any data type.For
instructions on basic usage, visit the [examples](/examples).

For installation, please go [here](#installation). For documentation, please go
[here](https://libvector-doxygen.netlify.app/).

### Step 3

Free the vector after use:

```c
vec_free(vec);
```

## Installation

Make sure to have [make](https://www.gnu.org/software/make/), [gcc](https://www.gnu.org/software/gcc/) and [git](https://git-scm.com/) installed.

```bash
git clone https://github.com/resyfer/libvector.git
cd libvector
make install
cd ..
rm -rf libvector
```

Provide the password when prompted.