TurboRLE: Turbo Run Length Encoding 
===================================

###### Efficient and fast **Run Length Encoding** library
- 100% C (C++ compatible headers), without inline assembly
<p>
- Efficient compression 
<p>
- Maximal 1 byte overhead
<p>
- No modification of the raw data, preserving compressibility
<p>
- Order preserving 

<p>
- **TRLE**: TurboRLE - Efficient and fast Run Length Encoding
<p>
- **SRLE**: TurboRLE Escape - Fast Run Length Encoding with automatic escape determination 
<p>
- **MRLE**: Mespotine RLE [MRLE](http://encode.ru/threads/2121-No-more-encoding-overhead-in-Run-Length-Encoding-Read-about-Mespotine-RLE-here-)
<p>
- **RLE64**: Run Length Encoding - [RLE64](http://sourceforge.net/projects/nikkhokkho/files/RLE64/)#

<p>
## Benchmark:
CPU: Sandy bridge i7-2600k at 4.5GHz, gcc 4.9, ubuntu 14.10
- Single thread
- Realistic and practical benchmark with large files

- Text File: [enwik9bwt](http://mattmahoney.net/dc/textdata.html) enwik9 bwt generated w. [libdivsufsort](https://code.google.com/p/libdivsufsort/)
<table>
<tr><th>File</th><th>Size</th><th>Ratio in %</th><th>C Time MB/s</th><th>D Time MB/s</th><th>Function</th></tr>
<tr><th>378458011</th><th>37.8</th><th>434.12</th><th>1446.38</th><th>trle v15-02</th></tr>
<tr><th>419346347</th><th>41.9</th><th>456.84</th><th>2167.74</th><th>srle v15-02</th></tr>
<tr><th>422296231</th><th>42.2</th><th>608.26</th><th>1209.34</th><th>rle64 8 v15-02</th></tr>
<tr><th>576619941</th><th>57.7</th><th>229.47</th><th>789.99</th><th>mrle v15-02</th></tr>
<tr><th>1000000008</th><th>100.0</th><th>5975.00</th><th>5975.00</th><th>memcpy</th></tr>
</table>
<p>
- Checkers program "End Game Table Base": [1034.db](http://encode.ru/threads/2077-EGTB-compression?p=41392&viewfull=1#post41392)
<table>
<tr><th>File</th><th>Size</th><th>Ratio in %</th><th>C Time MB/s</th><th>D Time MB/s</th><th>Function</th></tr>
<tr><th>82452160</th><th>19.7</th><th>560.01</th><th>2427.14</th><th>trle v15-02</th></tr>
<tr><th>88055360</th><th>21.0</th><th>272.68</th><th>1676.85</th><th>mrle v15-02</th></tr>
<tr><th>92539187</th><th>22.1</th><th>578.68</th><th>3188.59</th><th>srle v15-02</th></tr>
<tr><th>93905323</th><th>22.4</th><th>917.00</th><th>1368.14</th><th>rle64 8 v15-02</th></tr>
<tr><th>419225625</th><th>100.0</th><th>5975.00</th><th>5975.00</th><th>memcpy</th></tr>
</table>
<p>
- BMP File: [girl.bmp](http://sourceforge.net/projects/nikkhokkho/files/RLE64/)
<table>
<tr><th>File</th><th>Size</th><th>Ratio in %</th><th>C Time MB/s</th><th>D Time MB/s</th><th>Function</th></tr>
<tr><th>3293895</th><th>0.8</th><th>768.58</th><th>13058.49</th><th>trle v15-02</th></tr>
<tr><th>4482384</th><th>1.1</th><th>356.52</th><th>12899.49</th><th>mrle v15-02</th></tr>
<tr><th>4821158</th><th>1.2</th><th>770.65</th><th>13535.46</th><th>srle v15-02</th></tr>
<tr><th>8832643</th><th>2.2</th><th>1365.06</th><th>1933.86</th><th>rle64 8 v15-02</th></tr>
<tr><th>403920054</th><th>100.0</th><th>5942.90</th><th>5878.68</th><th>memcpy</th></tr> 
</table>

## Compile:
  gcc -O3 -march=native trle.c -o trle

## Usage:
  trle file

