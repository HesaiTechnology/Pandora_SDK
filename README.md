# Pandora_SDK
## Clone
```
git clone https://github.com/HesaiTechnology/Pandora_SDK.git --recursive
```

## Build
```
cd <project>
mkdir build ; cd build;
cmake .. ; make
```
## Add to your project 
### Cmake
```
add_subdirectory(<path_to>Pandora_SDK)

include_directories(
	<path_to>Pandora_SDK/include
	<path_to>Pandora_SDK/src/Pandar40P/include
)

target_link_libraries(<Your project>
  Pandora
)

```
### C++
```
#include "pandora/pandora.h"
```

