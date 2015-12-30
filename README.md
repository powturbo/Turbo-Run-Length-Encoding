TurboRLE: Turbo Run Length Encoding [![Build Status](https://travis-ci.org/powturbo/TurboRLE.svg?branch=master)](https://travis-ci.org/powturbo/TurboRLE)
===================================

###### Efficient and fastest **Run Length Encoding** library
- 100% C (C++ compatible headers), without inline assembly
<p>
- Most efficient compression 
- No other RLE compress or decompress faster with better compression
- :new: faster compression and 2x faster decompression with :+1: SIMD
- Compress better and up to 8 times faster and decompress up to 4 times faster than other fast RLEs
- Can be faster than memcpy
- :new: **ZERO!** byte overhead
  
<p>
- No modification of the raw data, preserving compressibility
- Order preserving 

###### TurboRLE
- **TRLE**: TurboRLE - Efficient and fast Run Length Encoding
<p>
- **SRLE**: TurboRLE Escape - Fast Run Length Encoding with automatic escape determination 

<p>
## Benchmark:
CPU: Sandy bridge i7-2600k at 4.2GHz, gcc 5.2, ubuntu 15.10
- with [TurboBench](https://github.com/powturbo/TurboBench)
- Single thread
- Realistic and practical benchmark with large files

###### Functions benchmarked
- **MRLE**: Mespotine RLE [MRLE](http://encode.ru/threads/2121-No-more-encoding-overhead-in-Run-Length-Encoding-Read-about-Mespotine-RLE-here-)
<p>
- **RLE64**: Run Length Encoding - [RLE64](http://sourceforge.net/projects/nikkhokkho/files/RLE64/)
<p>

- Text File: [enwik9bwt](http://mattmahoney.net/dc/textdata.html) enwik9 bwt generated w. [libdivsufsort](https://code.google.com/p/libdivsufsort/)

 (**bold** = pareto)  MB=1.000.000

|C Size|ratio%|C MB/s|D MB/s|Name|
|--------:|-----:|--------:|--------:|----------------|----------------|
|378458015| 37.8|**457.12**|**1908.41**|**trle**|
|419346351| 41.9|**606.05**|**4255.59**|**srle 8**|
|419346352| 41.9|491.16|4253.62|srle 0|
|422296235| 42.2|557.84|1364.10|**rle64 8**|
|487466207| 48.7|**1316.96**|4139.54|**srle 16**|
|498420792| 49.8|1113.81|2511.38|rle64 16|
|549218833| 54.9|**2682.93**|**6979.69**|**srle 32**|
|563503744| 56.4|**2730.54**|5073.81|**rle64 32**|
|576619945| 57.7|205.83|570.93|mrle|enwik9bwt|
|605766094| 60.6|**4779.21**|**7480.13**|**srle 64**|
|620676412| 62.1|**5247.28**|7376.44|**rle64 64**|
|1000000012|100.0|**8517.76**|**9176.59**|**memcpy**|

srle 0: RLE w/ auto escape
<p>
- Checkers program "End Game Table Base": [1034.db](http://encode.ru/threads/2077-EGTB-compression?p=41392&viewfull=1#post41392)

|C Size|ratio%|C MB/s|D MB/s|Name|
|--------:|-----:|--------:|--------:|----------------|----------------|
|82452164| 19.7|**652.87**|**3138.22**|**trle**|
|88055364| 21.0|233.07|1573.62|mrle|
|92539191| 22.1|**1147.88**|**5669.24**|**srle 8**|
|92539192| 22.1|794.21|5664.69|srle 0|
|93905327| 22.4|780.05|1659.48|rle64 8|
|113627625| 27.1|**1823.40**|5185.73|**srle 16**|
|117590491| 28.0|1341.02|2825.66|rle64 16|
|136924740| 32.7|**3306.88**|**7912.62**|**srle 32**|
|143953177| 34.3|2970.51|5506.36|rle64 32|
|165545036| 39.5|**5607.15**|**8081.80**|**srle 64**|
|176442237| 42.1|5090.87|7871.78|rle64 64|
|419225629|100.0|**8367.04**|**8934.25**|**memcpy**|

<p>
- BMP File: [girl.bmp in RLE64Samples](http://sourceforge.net/projects/nikkhokkho/files/RLE64/3.00/)

|C Size|ratio%|C MB/s|D MB/s|Name|
|--------:|-----:|--------:|--------:|----------------|----------------|
|3293899|  0.8|**1088.67**|**13113.37**|**trle**|
|4482388|  1.1|297.68|9209.99|mrle|
|4821162|  1.2|**10747.56**|13006.29|**srle 8**|
|4821163|  1.2|2099.00|13004.84|srle 0|
|8501660|  2.1|4578.31|10014.59|srle 16|
|8832647|  2.2|1274.23|2920.96|rle64 8|
|9265516|  2.3|2241.56|5721.46|rle64 16|
|13777939|  3.4|8099.79|10257.84|srle 32|
|15175482|  3.8|4609.31|9360.16|rle64 32|
|19872605|  4.9|**13497.36**|10169.71|**srle 64**|
|21910714|  5.4|8300.55|10232.33|rle64 64|
|403920058|100.0|8464.75|9160.88|memcpy|

## Compile:

        make

## Usage:

        ./trle file

### Environment:
###### OS/Compiler (32 + 64 bits):
- Linux: GNU GCC (>=4.6)
- clang (>=3.2) 
- Windows: MinGW

Last update: 30 DEC 2015

