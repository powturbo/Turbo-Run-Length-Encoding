TurboRLE: Turbo Run Length Encoding [![Build Status](https://travis-ci.org/powturbo/TurboRLE.svg?branch=master)](https://travis-ci.org/powturbo/TurboRLE)
===================================

##### Efficient and fastest **Run Length Encoding** library
  - :new: The fastest now up to 50% more faster incl. SSE/AVX2
  - 100% C (C++ compatible headers), without inline assembly
  - Most efficient compression 
  - No other RLE compress or decompress faster with better compression
  - :sparkles: faster compression and 2x faster decompression with :+1: SIMD
  - :+1: **Java** Critical Natives Interface. Access TurboRLE **incl. SIMD!** from Java
  - Compress better and up to 12 times faster and decompress up to 6 times faster than other fast RLEs
  - Can be faster than memcpy!
  - :+1: **ZERO!** byte overhead

  - No modification of the raw data, preserving compressibility for further postprocessing (ex. entropy coding)
  - Order preserving 

##### TurboRLE
  - **TRLE**: TurboRLE - Efficient and fast Run Length Encoding
  - **SRLE**: TurboRLE Escape - Fast Run Length Encoding with automatic escape determination 

## Benchmark:
- Single thread with [TurboBench](https://github.com/powturbo/TurboBench)
- Realistic and practical benchmark with large files and different distributions

###### External functions benchmarked
  - **[MRLE](http://encode.su/threads/2121-No-more-encoding-overhead-in-Run-Length-Encoding-Read-about-Mespotine-RLE-here-)**: Mespotine RLE
  - **[RLE8](https://github.com/rainerzufalldererste/rle8)**: A fast 8 bit Run Length Encoding (SSE/AVX2)
------------------------------------------------------------------------
#### CPU: Skylake i7-6700 3.4GHz, gcc 8.3 (2019-08)
- BMP File: [girl.bmp in RLE64Samples](http://sourceforge.net/projects/nikkhokkho/files/RLE64/3.00/)

(bold = pareto)  MB=1.000.000

|C Size|ratio%|C MB/s|D MB/s|Name / 2019-08|
|--------:|-----:|--------:|--------:|----------------|
|2623680|  0.6|**2074**|**11113**|**trle**|
|4148455|  1.0|2063|**12245**|**srle 0** (auto escape)|
|4482384|  1.1|378|**12302**|**mrle**|
|4744806|  1.2|**10766**|**12343**|**srle 8**|
|5901235|  1.5|861 |12092|   rle8 1|
|8431844|  2.1|7368|**12693**|**srle 16**|
|13722311|  3.4|**11090**|**13188**|**srle 32**|
|19839711|  4.9|**16269**|**13733**|**srle 64**|
|403920054|100.0|13978|**14001**|**memcpy**|

- Checkers program "End Game Table Base": [1034.db](http://encode.su/threads/2077-EGTB-compression?p=41392&viewfull=1#post41392)

|C Size|ratio%|C MB/s|D MB/s|Name / 2019-08|
|--------:|-----:|--------:|--------:|----------------|
|73108990| 17.4|**754**|**2983**|**trle**|
|84671759| 20.2|741|**5088**|**srle 0**|
|88055360| 21.0| 262|1491|   mrle|
|88666372| 21.2| 456| 2669| rle8 1|
|92369164| 22.0|**1019**|**5860**|**srle 8**|
|113561548| 27.1|**2028**|**7114**|**srle 16**|
|136918311| 32.7|**3588**|**9026**|**srle 32**|
|165547365| 39.5|**5972**|**10120**|**srle 64**|
|419225625|100.0|**13938**|**14017**|**memcpy**|

- Text File: [enwik9bwt](http://mattmahoney.net/dc/textdata.html) enwik9 bwt generated w. [libdivsufsort](https://code.google.com/p/libdivsufsort/)

|C Size|ratio%|C MB/s|D MB/s|Name / 2019-08|
|--------:|-----:|--------:|--------:|----------------|
|375094084| 37.5|**472**|**1743**|**trle**|enwik9bwt|
|415597104| 41.6|450|**3559**|**srle 0**|enwik9bwt|
|419263924| 41.9|**538**|**4256**|**srle 8**|enwik9bwt|
|487430623| 48.7|**1347**|**6287**|**srle 16**|enwik9bwt|
|549202860| 54.9|**2780**|**8238**|**srle 32**|enwik9bwt|
|576619941| 57.7|207|     553|   mrle|
|577685250| 57.8|260|   675|   rle8 1|
|605759578| 60.6|**5356**|**9471**|**srle 64**|enwik9bwt|
|1000000008|100.0|**13931**|**13926**|**memcpy**|enwik9bwt|

------------------------------------------------------------------------
- Post-processing with entropy coding<br> 
  direct entropy encoding after "trle" (no additional "move to front" or other transformation)

|C Size|ratio%|C MB/s|D MB/s|Name /             CPU Skylake 3.4 GHz (2019-06)|
|--------:|-----:|--------:|--------:|-----------------------------------------------|
|180510948| 18.1|**154**| **132**|**trle + TurboRC o0** (order 0 bitwise Range Coder)|
|187099490| 18.7|23|**2560**|**trle + TurboHF 0** (Huffman Coding)|
|192420471| 19.2|**1527**|**3834**|**trle + TurboANX 12** (Asymmetric Numeral Systems)|
|193455670| 19.3|**2192**|2986|**trle + TurboHF 12**|
|197974078| 19.8|1078|1406|trle + fse (Finite State Entropy)|
|229693376| 23.0|126|106|rle8 + TurboRC o0|
|254312056| 25.4|119|105|mrle + TurboRC o0|

for more info, see also: [Entropy Coder Benchmark](https://sites.google.com/site/powturbo/entropy-coder)

### Compile:

  		git clone git://github.com/powturbo/TurboRLE.git
        cd TurboRLE

##### Linux + Windows MingW 
 
  		make
        or
  		make AVX2=1

##### Windows Visual C++

  		nmake /f makefile.vs
        or
  		nmake AVX2=1 /f makefile.vs

## Usage:

        ./trle file
        ./trle -e# file

		# = function id (see file trle.c)

### Environment:

###### OS/Compiler (32 + 64 bits):
- Linux: GNU GCC (>=4.6)
- clang (>=3.2) 
- Intel ICC 19.0
- Windows: MinGW
- Windows: Visual c++

#### References
  - [Real-Time Compression of IEC 61869-9 Sampled Value Data](https://pure.strath.ac.uk/portal/files/55444712/Blair_etal_AMPS2016_Real_time_compression_of_IEC_61869_9_sampled_value_data.pdf)
  - [Understanding Compression: Data Compression for Modern Developers](https://books.google.de/books?id=2C2rDAAAQBAJ&pg=PA216&lpg=PA216&dq=%22turborle%22&source=bl&ots=TiLU4Qf47s&sig=tkk0Dnk9NnU0JMR3Z6iW4TRquxg&hl=de&sa=X&ved=0ahUKEwjZq-Li5uXSAhXFCJoKHe77B6cQ6AEIyAEwHQ#v=onepage&q=%22turborle%22&f=false)
  - [Understanding Compression](http://file.allitebooks.com/20160805/Understanding%20Compression.pdf)
  - [Entropy Coder Benchmark](https://sites.google.com/site/powturbo/entropy-coder)

Last update: 19 Aug 2019

