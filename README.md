# Nearest Neighbours using Locality Sensitive Hashing (LSH)
C++ program that, given a vectorised dataset and query set, performs locality sensitive hashing, finding either Nearest Neighbours (NN) or Neighbours in specified range of points in query set, using either Euclidian distance or Cosine Similarity.

![image](https://i.ibb.co/TbZ9c9b/rsz-lsh-algorithm.png)

**Source:** Slides from Ioannis Emiris lectures, 'Senior Project' course, DIT UoA

## The Problem
Consider an **d-dimensional dataset D**. Given a **query point q** (also d-dimensional), we need to find the **Nearest Neighbour (NN) of q** in D. The first thing that comes to mind is doing a Full Search. This works, but as the dataset grows, both in records and in dimensions, this method lacks in speed.

## A Solution
**Locality Sensitive Hashing (LSH)** seems to be a fair solution to this problem.
This method stores the points of the dataset in **L hash tables**, using **L "amplified" hash functions**.The hash functions are called "amplified" because the are actually a, random each time, **combination** of k hash functions. The set of these k hash functions is common for all the "amplified" functions, and each function has all of the functions but in a random order.

##### Thats good and all, but how does this help?
Now that the points are stored, its time for this method to shine. We hash **query point q** with **all of the amplified hash functions**, and create a set from the points in each bucket that each function assigned q. **Instead of looking through all of the points, we now have to find the NNs in this new set**, which is *probably* much smaller than the whole input set.

## Hash Functions
##### Euclidian Distance
Each and every one of the k hash functions has 3 parts:
1. `vector v`: A vector of d-dimensions, same as the input vectors. Each value is generated [normally](https://en.wikipedia.org/wiki/Normal_distribution) at the start of execution.

2. `double t`: Also generated at the start of execution but [uniformly](https://en.wikipedia.org/wiki/Uniform_distribution_(continuous)).

3. `int w`: "window". This is set as **400** in modules/EuclidianHashing.cpp, line 44. Feel free to experiment.

In order to hash a given point by one of the k hash functions the following formula will be used:
![equation](https://latex.codecogs.com/gif.latex?%5Cleft%20%5Clfloor%20%5Cfrac%7B%3Cx%2Cv%3E%20&plus;%20t%7D%7Bw%7D%20%5Cright%20%5Crfloor), where the < x, v > means **inner product**. **What actually happens is this:** Each input point is projected on the line of v, with an offset of t, divided into pieces of w length.

But each "Amplified" function has k of the above hash functions, so, the results of all of them are converted to strings, concatenated, and hashed using [std::hash](https://en.cppreference.com/w/cpp/utility/hash). Using the result, lets call that **res**, the position at the hash table is a result of:
![equation](https://latex.codecogs.com/gif.latex?pos%20%3D%20%28res%5C%3Amod%5C%3AM%29%5C%3Amod%5C%3ATableSize), 
with M being a **very large prime**. TableSize is by default **n/2**, where n is the total number of points in the input dataset. (This can be changed though by editing modules/EuclidianHashing.cpp, lines 14,104,165,177 and 268 and changing n/2 to desired value) 


Last but not least, the distance between point A and point B is calculated using [Euclidian Distance](https://en.wikipedia.org/wiki/Euclidean_distance), and thus the name of the method.
##### Cosine Similarity
Each hash functions in this method has just 1 part:

1. `vector Hash_Function`: A vector generated [normally](https://en.wikipedia.org/wiki/Normal_distribution).

First difference that you notice with the Euclidian method is that the size of each hash table is different (2^k instead of n/2). You can think the result of each application of an Amplified Function as a bit array (k bits), initialized with all zeros. First, the ![equation](https://latex.codecogs.com/gif.latex?%3Cx%2CHashFunction%5Bi%5D%3E) inner product is calculated, where x represents the input point. If the product is non-negative, the appropriate bit is set to 1. Doing this with all of the Hash Functions and "translating" the bit set into an integer gives us the position in the hash Table. Line 135 of modules/CosineHashing.cpp can state it even better than i can:
```
    if( sum >= 0 ) pos = pos + pow(2,h);
```
, where h is the position of the bit we are going to turn to 1.

Also, [Cosine Similarity](https://en.wikipedia.org/wiki/Cosine_similarity) is used to determine the distance between points. 

**Notice:** If you are going to try a range search using this method, be careful when you pick a radius, as it has a max value of **2**. That is because in order to calcualate the cosine similarity of vectors x and y, the following formula is used.
![equation](https://latex.codecogs.com/gif.latex?similarity%20%3D%201%20-%20%5Cfrac%7B%3Cx%2Cy%3E%7D%7B%5Cleft%20%5C%7C%20x%5Cright%20%5C%7C%5Cleft%20%5C%7C%20y%20%5Cright%20%5C%7C%7D) 
Notice that: ![equation](https://latex.codecogs.com/gif.latex?%5Cfrac%7B%3Cx%2Cy%3E%7D%7B%5Cleft%20%5C%7C%20x%5Cright%20%5C%7C%5Cleft%20%5C%7C%20y%20%5Cright%20%5C%7C%7D%20%3D%20cos%28%5Ctheta%29%2C%5C%3A%20%5Ctheta%5C%3A%20being%5C%3A%20the%5C%3A%20angle%20%5C%3A%20of%20%5C%3A%20x%20%5C%3A%20and%20%5C%3A%20y.), and thus the max value of range between vectors x and y being 2.
## Input
* **input_dateset**: As the name suggests, the input dataset. Each line contains one point, and each coordinate is divided by tabs. Example: 
```
5   4   3   2 
1   2   3   4 
7   8   9   12 
```
The dimension of all the points **must** be the same. These points will be stored in the L hash tables. You can find a more complex acceptable example in the **sample_datasets** directory.
* **query_dateset**: A file containing query points. The format here is the same as the one used in input_dataset. If what you want to do is a **range search**, you have to specify the radius of the search by writing `Radius: X` in the first line. An example of this can be found at the sample_datasets directory.
* **k and L**: These parameters can be specified with command line arguments. See Section *Compile and Run* for more info on this. 

## Output
* **output_file:** By the end of the execution, this file will contain the results of each query using both LSH and Full Search along with timing for each one. Neat!

## Compile and Run
1. A makefile is included in the repository. To compile just hit `$ make` or ` $ make lsh`.To delete the *lsh* binary file run `$ make clean`.
2. All of the parameters can be configured with command line arguments. To execute you can use `$ ./lsh -d <input_dataset> -q <query_dataset> -k <no_of_hash_functions> -L <no_of_hash_tables> -o <output_file_name -metric <euclidian or cosine>` There are default values (you may not provide them as arguments) for **k** (4), **L** (5) and **metric** (euclidian).



