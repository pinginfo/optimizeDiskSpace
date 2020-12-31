# OptimizeDiskSpace
OptimizedDiskSpace allows to replace all duplicate files in one link to save disk space. 
This application can be used to save space in image backup hard drives for example.

## Install

```
git clone https://github.com/pinginfo/optimizeDiskSpace.git
cd optimizeDiskSpace
make
./optimizeDiskSpace <path> [OPTION]
```

## Usage

Show all duplicate files.
```
./optimizeDiskSpace <path> -V
```

Remplace all duplicate files with a link.
```
./optimizeDiskSpace <path> -R
```

## Disclaimer
This software to damage your system in case of misuse. Never run it with root rights.

## License
`optimizeDiskSpace` is released under [GNU General Public License ][license]

OptimizedDiskSpace Copyright (C) 2020 Guillaume Pin 


[license]: https://www.gnu.org/licenses/gpl-3.0.html
