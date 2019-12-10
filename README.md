# <p align=center> :mortar_board: SpyCBlock :microscope: </p>

SpyCBlock is an accademics software for analiaze the blk file of Bitcoin blockchain Mainet.
This is an explerimental version and it want to demostration that is possible work with only file blk.

SpyCBlo is a simple parser bitcoin blk file, with this parser is possible do some serialization, how:

- Serialization Transaction Graph (:heavy_check_mark:);
- Serialization complete Blockchain to JSON (:heavy_check_mark:);
- Serialization Address Graph (:warning:).

For reduce the space of serialization Transaction graph, is possible use the library [ZLib](https://github.com/madler/zlib) for compress the information; with this code is possible uncompressed the data.

```c++
void decompressFileWithZLib()
{
    std::string filename = "YOUR_PATH/blkXXXXX.dat";
    gzFile inFileZ = gzopen(filename.c_str(), "rb");

    if(inFileZ == NULL){
        printf("Error: Failed to gzopen %s\n", filename.c_str());
        exit(0);
    }
    unsigned char unzipBuffer[8192];
    unsigned int unzippedBytes;
    std::vector<unsigned char> unzippedData;
    while (true)
    {
        unzippedBytes = gzread(inFileZ, unzipBuffer, 8192);
        if(unzippedBytes > 0) {
            unzippedData.insert(unzippedData.end(), unzipBuffer, unzipBuffer + unzippedBytes);
        }else{
            break;
        }
    }

    for(auto &character : unzippedData)
    {
        if(character == '.'){
            std::cout << "\n";
        }else{
            std::cout << character;
        }
    }
}
```

Is possible execute the parser with the library [OpenMP](https://www.openmp.org/) for execution data with multi-core an this is a simple velocity benchmark.

_PS: for the moment the parser use all core of the CPU is the multicore propriety is enabled._

![benchmark_image](imgs/benchmark.png)


The graph of transactions form is describe [here](#todo) and this is an example for visualize this with Web app, [this is](https://github.com/vincenzopalazzo/SpyJSBlock.react) an simple demo.

_The screenshot of transaction graph_

![transaction_graph](imgs/graph_tx.png)

_The screenshot of address graph subdivise to class (with luvain algorithm)_

![address_graph](imgs/address_graph.png)

## JSON version Bitcoin Blockchain

Have the version of Bitcoin blockchain to JSON is parwerfool because is possible work on the JSON format, With this is possible create easy analisis on Bitcoin network.

An example: I have create a simple analisis with [AnalytcsPyBlock](https://github.com/vincenzopalazzo/AnalyticsPyBlock) to get information from type of script utilized in the Bitcoin blockchain; this is the result and [here](https://vincenzopalazzo.github.io/AnalyticsPyBlock/) is avaible the web version

![analisis_script](imgs/result-global.png)
