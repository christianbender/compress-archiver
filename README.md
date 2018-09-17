## compress - Archiver

This project is a simple archiver for images (jpg-files). The images can be writed in a single file. Or can be encrypt or decrypt. The program used the [XOR-cipher](https://en.wikipedia.org/wiki/XOR_cipher)

**warning:** The encrypt and decrypt algorithm isn't save! Keys can be only between 0 and 255 !  

### Build  

#### Dependencies  

* gcc --- C-compiler

#### Build the program  

For building the project type in the console:  
```bash
$ make
```
After that you get the executable ```compress```. 

#### Tidy up

For cleaning type in the console  
```bash
$ make clean
```

### Using  

You fill find some example images in the directory **images**. (CC0 license)  
* [baum1](https://pixabay.com/de/nebel-nadelwald-fichten-wald-gr%C3%BCn-3622519/)  
* [baum2](https://pixabay.com/de/einsamer-baum-baum-eiche-wolken-1934897/)

For create a simple archive:  
```bash
$ ./compress -c images/baum1.jpg images/baum2.jpg  
```

You get a file called ```out```.  

For extracting the file ```out```:  
```bash
$ ./compress -e out 
```

#### For encryption and decryption  

For encrypt a simple archive:  
```bash
$ ./compress -en KEY images/baum1.jpg images/baum2.jpg  
```

* ```KEY``` can be a value between 0 up to 255.  

For decrypt a simple archive:  
```bash
$ ./compress -de KEY out 
```

**warning:** The encrypt and decrypt algorithm isn't save! Keys can be only between 0 and 255 !  
